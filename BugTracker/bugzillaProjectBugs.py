import requests
import sys
import json
import time
import pymongo

base_url = sys.argv[1]
project = sys.argv[2]
output_host = sys.argv[3]
output_db = sys.argv[4]
output_collection = sys.argv[5]
# output_file = sys.argv[3]

coll = pymongo.MongoClient(output_host)[output_db][output_collection]

url = base_url + '/rest/bug?product=' + project
offset = 0
batch = 1000
done = False
while done == False:
    print '%06d' % offset
    content = requests.get(url + '&limit=' + str(batch) + '&offset=' + str(offset)).content
    loaded = json.loads(content)
    if len(loaded["bugs"]) > 0:
        coll.insert(loaded["bugs"])
        # json.dump(loaded["bugs"], open(('%06d' % offset) + '-' + output_file, 'w'), indent=2)
    else:
        done = True
    offset += batch
    print 'sleeping 10s...'
    time.sleep(10)
