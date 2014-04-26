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
      messages[message_id]['From']={}
      messages[message_id]['From'][message_from]=''

      people[message_from]={}
      people[message_from]['Send']={}
      people[message_from]['Send'][message_id]=''

    if message_date:
      messages[message_id]['Date']={}
      messages[message_id]['Date'][message_date]=''

    if message_reply:
      messages[message_id]['ReplyTo']={}
      messages[message_id]['ReplyTo'][message_reply]=''

for message in mbox:
  message_id = message['Message-Id']
  message_reply = message['In-Reply-To']
  message_from = message['From']

  if message_reply:
    if message_reply in messages:
      previous_message = messages[message_reply]

      if previous_message:
        recipient = previous_message['From'].itervalues().next()

        if recipient:
          messages[message_id]['To']={}
          messages[message_id]['To'][recipient]=''

          people[recipient]['Received']={}
          people[recipient]['Received'][message_id]=''

          sender = message_from
          people[recipient]['ReceivedFrom'][message_from][message_id]=''
          people[sender]['ReceivedFrom'][recipient][message_id]=''

for person in people:
  print person,' ', len(person)

