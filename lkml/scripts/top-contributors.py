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
    n = int(sys.argv[2])

    with open(filename) as f:
        contribs = json.load(f)

    counts = {}
    for c in contribs:
        year = c["_id"]["year"]
        count = c["value"]

        if year not in counts:
            counts[year] = []

        counts[year].append(count)

    print '"Year", "Total Emails", %s' % (", ".join(['Top %d' % (i) for i in range(1,n+1)]))
    for year in counts:
        counts[year].sort(lambda x, y: y - x)

        print "%d, %d, %s" % (year, sum(counts[year]), ", ".join(map(str, partials(counts[year], n))))

if __name__ == "__main__":
    sys.exit(main())
