from bs4 import BeautifulSoup
import requests
import sys
import time
import dateutil.parser
import pymongo

list = sys.argv[1]
host = sys.argv[2]
db = sys.argv[3]
collection = sys.argv[4]

coll = pymongo.MongoClient(host)[db][collection]

base = 'http://marc.info/'

html = requests.get(base + '?l=' + list).text

soup = BeautifulSoup(html)


def extract_year(href):
    if href and href.find('&b=') != -1:
        return int(href.split('b=')[1].split('&')[0])/100
    return None


months = []
for link in soup.find_all('a'):
    href = link.get('href')
    year = extract_year(href)
    if year and year > 2010:
        months.append(href)

message_set = set()
message_links = []


def extract_message_id(href):
    if href and href.find('&m=') != -1:
        return int(href.split('m=')[1].split('&')[0])
    return None


def extract_list(href):
    if href and href.find('?l=') != -1:
        return href.split('l=')[1].split('&')[0]
    return None


def find_new_message(link):
    href = link.get('href')
    message_id = extract_message_id(href)
    message_list = extract_list(href)
    if message_list == list and message_id and message_id not in message_set:
        message_set.add(message_id)
        message_links.append(href)


for month_link in months:
    print(month_link)
    month_soup = BeautifulSoup(requests.get(base + month_link).text)
    for link in month_soup.find_all('a'):
        find_new_message(link)
    time.sleep(2)

while len(message_links) > 0:
    message_link = message_links.pop()
    print(message_link + ': ' + str(len(message_links)) + ' remaining')
    message = {'_id': extract_message_id(message_link)}
    message_soup = BeautifulSoup(requests.get(base + message_link).text)
    for link in message_soup.find_all('a'):
        find_new_message(link)
        href = link.get('href')
        if href and href.find('?a=') != -1:
            message['from'] = link.text
        elif href and href.find('&b=') != -1:
            message['date'] = dateutil.parser.parse(link.text)
        elif link.text == 'prev in thread':
            message['replyto'] = extract_message_id(href)
    coll.insert(message)
    time.sleep(2)

print(message_set)
