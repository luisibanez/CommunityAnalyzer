import sys
import pymongo
import dateutil.parser

host = sys.argv[1]
db = sys.argv[2]
input_collection = sys.argv[3]
output_collection = sys.argv[4]

in_coll = pymongo.MongoClient(host)[db][input_collection]
out_coll = pymongo.MongoClient(host)[db][output_collection]

i = 0
batch = 1000
docs = []
for d in in_coll.find():
    d['creation_time'] = dateutil.parser.parse(d['creation_time'])
    d['last_change_time'] = dateutil.parser.parse(d['last_change_time'])
    docs.append(d)
    i += 1
    if i % batch == 0:
        out_coll.insert(docs)
        docs = []
        print i

out_coll.insert(docs)
