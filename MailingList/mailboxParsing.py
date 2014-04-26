#!/usr/bin/env python

import mailbox

mbox = mailbox.mbox('/home/ibanez/data/ITK/Community/MailingList/python/ITKUsers.txt')

people = {}
messages = {}

for message in mbox:
  message_id = message['Message-Id']
  message_from = message['From']
  message_reply = message['In-Reply-To']
  message_date = message['Date']

  if message_id:
    messages[message_id]={}

    if message_from:
      # remove charactes from email source after the open parenthesis
      sender = message_from.split("(")[0].lower()

      messages[message_id]['From']={}
      messages[message_id]['From'][sender]={}

      if sender not in people:
        people[sender]={}
        people[sender]['Send']={}

      people[sender]['Send'][message_id]={}

    if message_date:
      messages[message_id]['Date']={}
      messages[message_id]['Date'][message_date]={}

    if message_reply:
      messages[message_id]['ReplyTo']={}
      messages[message_id]['ReplyTo'][message_reply]={}

for message in mbox:
  message_id = message['Message-Id']
  message_reply = message['In-Reply-To']
  message_from = message['From']

  if message_reply:
    if message_reply in messages:
      previous_message = messages[message_reply]

      if previous_message:
        recipientlist = previous_message['From']

        if recipientlist:

          recipient = recipientlist.iterkeys().next()

          current_message = messages[message_id]

          if 'To' not in current_message:
            current_message['To']={}

          current_message['To'][recipient]={}

          person = people[recipient]

          if 'Received' not in person:
            person['Received']={}

          person['Received'][message_id]={}

          # remove charactes from email source after the open parenthesis
          sender = message_from.split("(")[0].lower()

          if 'ReceivedFrom' not in person:
            person['ReceivedFrom']={}

          receivedmessages = person['ReceivedFrom']

          if sender not in receivedmessages:
            receivedmessages[sender]={}

          receivedmessages[sender][message_id]={}




# sort the people dictionary by key
sorted(people, key=people.get)

# list of people with number of emails sents and received
for personid in people:
  person = people[personid]
  if person:
    sent = person['Send']
    number_of_emails_sent = len(sent)
    number_of_emails_received = 0
    if 'Received' in people[personid]:
      received = person['Received']
      number_of_emails_received = len(received)
    print personid,' ',number_of_emails_sent,' ',number_of_emails_received



print "Number of messages ",len(messages)
print "Number of people ",len(people)

