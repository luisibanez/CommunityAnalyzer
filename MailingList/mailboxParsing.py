#!/usr/bin/env python

import mailbox
import email.utils
from datetime import datetime
from dateutil.parser import parse

mbox = mailbox.mbox('/home/ibanez/data/ITK/Community/MailingList/python/ITKUsers.txt')

people = {}
messages = {}
threads = {}

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

# list of people with number of emails sents and received
def listNumberOfEmailsSentAndReceived(people):

 for personid in people:
   person = people[personid]
   if person:
     sent = person['Send']
     number_of_emails_sent = len(sent)
     number_of_emails_received = 0
     if 'Received' in people[personid]:
       received = person['Received']
       number_of_emails_received = len(received)
     print personid,',',number_of_emails_sent,',',number_of_emails_received


def countNumberOfReplyMessages(messages):
  replyCount = 0
  messagesCount = 0
  for msg in messages:
    messagesCount += 1
    if 'ReplyTo' in messages[msg]:
      replyCount += 1

  print "Number of messages ",len(messages)
  print "Number of replies ",replyCount
  print "Number of messages ",messagesCount


def forwardLinkMessages(messages):
  for messageid in messages:
    if 'ReplyTo' in messages[messageid]:
      messageitr = messages[messageid]['ReplyTo'].iterkeys().next()
      # print messageid,' ReplyTo ',messageitr
      if messageitr in messages:
        if not 'FollowedBy' in messages[messageitr]:
          messages[messageitr]['FollowedBy']={}
        messages[messageitr]['FollowedBy'][messageid]={}
        # print messageitr,' FollowedBy ',messageid


def composeThreads(messages,threads):
  for messageid in messages:
    if not 'ReplyTo' in messages[messageid]:
      if not messageid in threads:
        threads[messageid]={}
        threads[messageid]['Messages']={}
        threads[messageid]['Messages'][messageid]={}
        if not 'Thread' in messages[messageid]:
          messages[messageid]['Thread']={}
        messages[messageid]['Thread'][messageid]={}

        notEndOfThread = True

        currentmessageid = messageid
        while notEndOfThread:
          if 'FollowedBy' in messages[currentmessageid]:
            notEndOfThread = True
            nextmessageid = messages[currentmessageid]['FollowedBy'].iterkeys().next()
            threads[messageid]['Messages'][nextmessageid]={}
            currentmessageid = nextmessageid
          else:
            notEndOfThread = False


def reportThreads(messages,threads):
  for thr in threads:
    print thr, len(threads[thr]['Messages'])
  print 'total ',len(threads),' threads'


def threadsSizeHistogram(threads):
  histogram={}
  for threadid in threads:
    size = len(threads[threadid]['Messages'])
    if size in histogram:
      histogram[size] += 1
    else:
      histogram[size] = 1

  totalMessages = 0
  totalThreads = 0

  for binplace in histogram:
    print binplace,' = ',histogram[binplace]
    totalThreads += histogram[binplace]
    totalMessages += histogram[binplace] * binplace

  print 'Total threads = ',totalThreads
  print 'Total messages = ',totalMessages


for message in mbox:
  message_id = message['Message-Id']
  message_from = message['From']
  message_reply = message['In-Reply-To']
  message_date = message['Date']

  if message_id:
    messages[message_id]={}

    if message_from:
      # remove charactes from email source after the open parenthesis
      sender = regularizeEmail(message_from)

      messages[message_id]['From']={}
      messages[message_id]['From'][sender]={}

      if sender not in people:
        people[sender]={}
        people[sender]['Send']={}

      people[sender]['Send'][message_id]={}

    if message_date:

      message_date = message_date.split("(")[0]

      messages[message_id]['Date']={}
      messages[message_id]['Date'][message_date]={}

      message_datetime = parse(message_date)

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
          sender = regularizeEmail(message_from)

          if 'ReceivedFrom' not in person:
            person['ReceivedFrom']={}

          receivedmessages = person['ReceivedFrom']

          if sender not in receivedmessages:
            receivedmessages[sender]={}

          receivedmessages[sender][message_id]={}




# sort the people dictionary by key
sorted(people, key=people.get)

listNumberOfEmailsSentAndReceived(people)

countNumberOfReplyMessages(messages)

forwardLinkMessages(messages)

composeThreads(messages,threads)

reportThreads(messages,threads)

threadsSizeHistogram(threads)

print 'People = ',len(people)
