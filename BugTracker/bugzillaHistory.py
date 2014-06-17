import requests
import sys
import pymongo
import json

base_url = sys.argv[1]
host = sys.argv[2]
db = sys.argv[3]
input_collection = sys.argv[4]
output_collection = sys.argv[5]

in_coll = pymongo.MongoClient(host)[db][input_collection]
out_coll = pymongo.MongoClient(host)[db][output_collection]

url = base_url + '/rest/bug/'
for d in in_coll.find(sort=[('creation_time', pymongo.DESCENDING)]):
    print d['creation_time']
    content = requests.get(url + str(d['id']) + '/history').content
    loaded = json.loads(content)
    d['history'] = loaded['bugs'][0]['history']
    out_coll.insert(d)
