import json
import sys

# Given a time in seconds, returns the number of whole months represented.
def months(t):
    return int(t / 60 / 60 / 24 / 30)

# Given a time in seconds, returns the number of whole days represented.
def days(t):
    return int(t / 60 / 60 / 24)

def hours(t):
    return int(t / 60 / 60)

def minutes(t):
    return int(t / 60)

def histogram(v):
    # Get the unique values in the list.
    uniq = list(set(v))

    return {k: len(filter(lambda x: x == k, v)) for k in uniq}

def vega_data(h):
    data = []
    for k, v in h.iteritems():
        data.append({"x": k,
                     "y": v})

    return data

def dump_negative_keys(h):
    hh = h.copy()
    for k in filter(lambda x: x < 0, hh.keys()):
        del hh[k]

    return hh

def filter_keys(f, d):
    dd = d.copy()
    for k in filter(lambda x: not f(x), dd.keys()):
        del dd[k]

    return dd

def save_json(data, filename):
    with open(filename, "w") as f:
        #print >>f, json.dumps(data, sort_keys=True, indent=4)
        print >>f, json.dumps(data, indent=4)

def main():
    if len(sys.argv) < 2:
        times = json.loads(sys.stdin.read())
    else:
        f = open(sys.argv[1])
        times = json.loads(f.read())
        f.close()

    # Compute time-based indices.
    monthtimes = map(months, times)
    daytimes = map(days, times)
    hourtimes = map(hours, times)
    minutetimes = map(minutes, times)

    # Compute histograms.
    monthhist = histogram(monthtimes)
    dayhist = histogram(daytimes)
    hourhist = histogram(hourtimes)
    minutehist = histogram(minutetimes)

    # Throw away negative values.
    monthhist = dump_negative_keys(monthhist)
    dayhist = dump_negative_keys(dayhist)
    hourhist = dump_negative_keys(hourhist)
    minutehist = dump_negative_keys(minutehist)

#    # Limit upper values as well.
    #dhist = filter_keys(lambda x: x < 30, dhist)

    # Compute a Vega data table.
    monthhist_vega = vega_data(monthhist)
    dayhist_vega = vega_data(dayhist)
    hourhist_vega = vega_data(hourhist)
    minutehist_vega = vega_data(minutehist)

    save_json(monthhist_vega, "month.json")
    save_json(dayhist_vega, "day.json")
    save_json(hourhist_vega, "hour.json")
    save_json(minutehist_vega, "minute.json")

    return 0

if __name__ == "__main__":
    sys.exit(main())
