import calendar
import requests
import gzip
import StringIO
import mailbox
import tempfile
import os

import sys
import json

list_url = sys.argv[1]
output_file = sys.argv[2]

data = b''

for year in range(2002, 2014):
    for month in calendar.month_name[1:]:
        url = list_url + str(year) + '-' + month + '.txt.gz'
        print url
        data += requests.get(url).content

fd, path = tempfile.mkstemp()
print path
file = os.fdopen(fd, 'w')
file.write(data)
file.close()
mbox = mailbox.mbox(path)

def regularizeEmail( inputemail ):
    simplifiedemail = message_from.split("(")[0].lower()

    basename = ''
    domain = ''

    if ' at ' in simplifiedemail:
        basename = simplifiedemail.split(' at ')[0]
        domain = simplifiedemail.split(' at ')[1]

    if '@' in simplifiedemail:
        basename = simplifiedemail.split('@')[0]
        domain = simplifiedemail.split('@')[1]

    basename.strip()
    domain.strip()

    recomposedemail = basename+'@'+domain
    return recomposedemail

people_map = {}
messages = []

for message in mbox:
    message_id = message['Message-Id']
    message_from = message['From']
    message_reply = message['In-Reply-To']
    message_date = message['Date']

    if not message_id:
        continue

    m = {'Id': unicode(message_id, errors='replace').strip()}
    if message_from:
        sender = regularizeEmail(message_from)

        m['From'] = unicode(sender, errors='replace').strip()

        if sender not in people_map:
            people_map[sender] = {'Sent': []}

        people_map[sender]['Sent'].append(message_id)

    if message_date:
        m['Date'] = unicode(message_date.split("(")[0], errors='replace').strip()

    if message_reply:
        m['ReplyTo'] = unicode(message_reply, errors='replace').strip()
    else:
        m['ReplyTo'] = ''

    messages.append(m)

os.remove(path)

json.dump(messages, open(output_file, 'w'), indent=2)
