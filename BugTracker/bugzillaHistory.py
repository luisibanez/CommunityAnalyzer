import requests
import sys
import pymongo
import json
import time

base_url = sys.argv[1]
host = sys.argv[2]
db = sys.argv[3]
input_collection = sys.argv[4]
output_collection = sys.argv[5]

in_coll = pymongo.MongoClient(host)[db][input_collection]
out_coll = pymongo.MongoClient(host)[db][output_collection]

url = base_url + '/rest/bug/'
for d in in_coll.find(sort=[('creation_time', pymongo.DESCENDING)], timeout=False):
    print d['creation_time']
    if out_coll.find_one({'id': d['id']}):
        continue
    content = requests.get(url + str(d['id']) + '/history').content
    loaded = json.loads(content)
    d['history'] = loaded['bugs'][0]['history']
    out_coll.insert(d)
    time.sleep(1)
