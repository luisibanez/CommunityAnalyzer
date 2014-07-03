import json
import sys

def partials(nums, n):
    total = 0
    for i in range(n):
        if i >= len(nums):
            return
        total += nums[i]
        yield total

def main():
    global counts

    filename = sys.argv[1]
    p = map(float, sys.argv[2:])
    p.sort()

    with open(filename) as f:
        contribs = json.load(f)

    counts = {}
    for c in contribs:
        year = c["_id"]["year"]
        count = c["value"]

        if year not in counts:
            counts[year] = []

        counts[year].append(count)

    print '"Year", "Total Emails", "Total Emailers", %s' % (", ".join(['"Top %.00f%% (emailers)"' % (v) for v in p]))
    for year in counts:
        counts[year].sort()
        counts[year].reverse()
        vals = counts[year]

        total = sum(vals)
        emailers = len(vals)

        thresh = []
        i = 0
        running = 0
        for j in xrange(emailers):
            running += vals[j]
            if float(running) / total > p[i] / 100.0:
                thresh.append(j + 1)
                i += 1

                if i == len(p):
                    break

        print "%d, %d, %d, %s" % (year, total, emailers, ", ".join(map(str, thresh)))

if __name__ == "__main__":
    sys.exit(main())
