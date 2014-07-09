import sys
import pymongo
import datetime
from dateutil.relativedelta import relativedelta
from operator import itemgetter
import dateutil.parser
import dateutil.rrule

host = sys.argv[1]
db = sys.argv[2]
collection = sys.argv[3]

coll = pymongo.MongoClient(host)[db][collection]

min_date = coll.aggregate([{'$group': {'_id': 0, 'minDate': {'$min': '$creation_time'}}}])['result'][0]['minDate']
max_date = coll.aggregate([{'$group': {'_id': 0, 'maxDate': {'$max': '$creation_time'}}}])['result'][0]['maxDate']

# Go to beginning of month
min_date = datetime.datetime(min_date.year, min_date.month, 1)

months = dateutil.rrule.rrule(dateutil.rrule.MONTHLY, dtstart=min_date, until=max_date)

data = []
print 'Date,Count,History,MeanResponseHours,Top5ContributorPercent'
for m in months:
    count = 0
    hcount = 0
    hresponse = 0
    activity = {}
    activity_count = 0
    for d in coll.find({'creation_time': {'$gte': m, '$lt': (m + relativedelta(months=1))}}):
        creator = d['creator_detail']['email']
        if creator not in activity:
            activity[creator] = 0
        activity[creator] += 1
        activity_count += 1
        if len(d['history']) > 0:
            hcount += 1
            when = d['history'][0]['when']
            if isinstance(when, (str, unicode)):
                when = dateutil.parser.parse(when, ignoretz=True)
            hresponse += (when - d['creation_time']).total_seconds()
            for h in d['history']:
                who = h['who']
                if who not in activity:
                    activity[who] = 0
                activity[who] += 1
                activity_count += 1
        count += 1
    items = activity.items()
    items.sort(key=itemgetter(1), reverse=True)
    activity_top5 = 0
    for i in range(5):
        activity_top5 += items[i][1]
    print str(m.date()) + ',' + str(count) + ',' + str(hcount) + ',' + str(hresponse/hcount/3600) + ',' + str(float(activity_top5)/activity_count)
