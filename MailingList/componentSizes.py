import networkx
import operator
import json
import sys

inputFile = sys.argv[1]
outputFile = sys.argv[2]
source = 'ReplyTo'
target = 'Id'

input = json.load(open(inputFile))

g = networkx.Graph()

for row in input:
    s = row[source].strip()
    t = row[target].strip()
    g.add_node(s)
    g.add_node(t)
    if s != "" and t != "":
        g.add_edge(s, t)

comp = networkx.connected_components(g)

sizes = {}
for c in comp:
    s = sizes.get(len(c), 0)
    sizes[len(c)] = s + 1

output = [{"size": s, "count": sizes[s]} for s in sizes]
output = {"fields": ["size", "count"], "rows": sorted(output, key=operator.itemgetter("size"))}

json.dump(output["rows"], open(outputFile, 'w'), indent=2)
