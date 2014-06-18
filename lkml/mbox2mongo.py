import argparse
import bson.json_util
import dateutil.parser
import os
import sys

def parse_email(text):
    # Split into lines, and look for a blank line - this separates headers from
    # body.
    lines = text.split("\n")
    try:
        brk = lines.index("")
    except ValueError:
        headers = text
        body = ""
    else:
        headers = "\n".join(lines[:brk])
        body = "\n".join(lines[brk+1:])

    # Line continuations are represented by a linebreak followed by a tab (i.e.,
    # continuation lines simply begin with a tab character).  However, some
    # lines begin with a series of spaces - convert these to the tab
    # format.
    headers = "\n".join(map(lambda x: "\t" + x.lstrip() if x[0] == " " else x, headers.split("\n")))

    # Condense continued lines into single lines.
    headers = headers.replace("\n\t", " ")

    # Parse the headers: each line is a header name followed by a colon and
    # space, followed by the header value.
    try:
        headers = {k: v for k, v in map(lambda x: x.split(": ", 1), headers.split("\n"))}
    except ValueError:
        print headers
        return

    # Convert the date fields to datetime objects.
    if "(" in headers["Date"]:
        headers["Date"] = " ".join(headers["Date"].split()[:-1])
    headers["Date"] = dateutil.parser.parse(headers["Date"])
    #headers["NNTP-Posting-Date"] = dateutil.parser.parse(headers["NNTP-Posting-Date"])

    # Attach the email body to the record.
    headers["Body"] = body

    return headers

def stream_mbox(filename):
    def is_mbox_header(l):
        return len(l) >=5 and l[:5] == "From "

    with open(filename) as f:
        # Throw out the first line, after verifying that it starts with "From "
        # (note the trailing space).
        line = f.readline()
        if not is_mbox_header(line):
            raise ValueError("'%s' does not appear to be an mbox file")

        # Read lines into a buffer until the mbox separator appears.
        #
        # The "mbox separator" is three blank lines followed by a line starting
        # with "From " (note the trailing space, and lack of colon).
        buf = []
        while True:
            line = f.readline()

            if line == "":
                # End-of-file.  Yield the last email, then stop.
                yield "".join(buf)
                return
            elif line == "\n":
                # Probe for the separator.
                lines = [line] + [f.readline(), f.readline(), f.readline()]
                if lines[1] == "\n" and lines[2] == "\n" and is_mbox_header(lines[3]):
                    yield "".join(buf)
                    buf = []
                else:
                    buf += filter(lambda x: len(x) > 0, lines)
            else:
                # Save the line and continue.
                buf.append(line)

def main2():
    ap = argparse.ArgumentParser(description="Process NNTP email files or directories.")
    ap.add_argument("files", metavar="FILE", nargs="+", help="Files to process")
    ap.add_argument("--progress", "-p", metavar="N", type=int, default=0, help="Display periodic progress reports every N records")
    ap.add_argument("--verbose", "-v", action="store_true", help="Show what is happening as it happens")

    args = ap.parse_args()

    bad = []
    for filename in args.files:
        if args.verbose:
            sys.stderr.write("processing file '%s'%s" % (filename, "..." if args.progress == 0 else ""))
            sys.stderr.flush()

        mbox = stream_mbox(filename)
        failure = False
        for i, email in enumerate(mbox):
            try:
                print bson.json_util.dumps(parse_email(email))
            except UnicodeDecodeError as e:
                if args.verbose:
                    failure = True

                bad.append({"file": filename,
                            "number": i + 1,
                            "message": "UnicodeDecodeError: %s" % (str(e))})

            if args.verbose and args.progress > 0 and i % args.progress == 0:
                sys.stderr.write("*" if failure else ".")
                failure = False

        if args.verbose:
            print >>sys.stderr, "ok"

    if len(bad) > 0:
        print >>sys.stderr, "%d email%s %s skipped due to errors:" % (len(bad), "s" if len(bad) > 1 else "", "were" if len(bad) > 1 else "was")
    report = "\n".join(map(lambda x: "%s:%d %s" % (x["file"], x["number"], x["message"]), bad))
    print >>sys.stderr, report

    return 0
     


def main():
    ap = argparse.ArgumentParser(description="Process NNTP email files or directories.")
    ap.add_argument("--file", "-f", metavar="FILE", type=str, help="A single file to process (default: STDIN)")
    ap.add_argument("--dir", "-d", metavar="DIR", type=str, help="A directory of files to process")
    ap.add_argument("--progress", "-p", metavar="N", type=int, default=0, help="Display periodic progress reports every N records")
    ap.add_argument("--verbose", "-v", action="store_true", help="Show what is happening as it happens")

    args = ap.parse_args()

    # Create a list of files to process.
    if args.file and args.dir:
        print >>sys.stderr, "cannot specify both --file and --dir"
        return 1
    elif args.file:
        files = [args.file]
    elif args.dir:
        files = map(lambda x: args.dir + os.path.sep + x, filter(lambda y: y[0] != ".", os.listdir(args.dir)))
    else:
        print >>sys.stderr, "must specify one of --file or --dir"
        return 1

    # Process the files.
    bad = []
    for i, filename in enumerate(files):
        if args.verbose:
            sys.stderr.write("processing file '%s'..." % (filename))
            sys.stderr.flush()

        with open(filename) as f:
            text = f.read()

        try:
            print bson.json_util.dumps(parse_email(text))
        except UnicodeDecodeError as e:
            if args.verbose:
                print >>sys.stderr, "failed (skipping)"

            bad.append({"file": filename,
                        "message": "UnicodeDecodeError: %s" % (str(e))})
        else:
            if args.verbose:
                print >>sys.stderr, "ok"

        if args.progress > 0 and i % args.progress == 0:
            print >>sys.stderr, "processed %d of %d files" % (i, len(files))

    if len(bad) > 0:
        print >>sys.stderr, "%d file%s %s skipped due to errors:" % (len(bad), "s" if len(bad) > 1 else "", "were" if len(bad) > 1 else "was")
    report = "\n\n".join(map(lambda x: "%s\n%s" % (x["file"], x["message"]), bad))
    print >>sys.stderr, report

    return 0
    

if __name__ == "__main__": 
    sys.exit(main2())
