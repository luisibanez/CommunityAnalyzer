CommunityAnalyzer
=================

Scripts for analyzing community activity and structure

Linux Kernel Mailing List
-------------------------

The ``lkml`` directory contains scripts for working with Linux Kernel mailing
list archives.

**Retrieving data.** To retrieve mailing list data, the easiest way is to use
Gmane's HTTP interface to the messages.

1. Make sure you have ``curl`` installed.

2. Create a directory to hold the data:

    mkdir ~/lkml-archives
    cd ~/lkml-archives

4. Run the ``lkml/download-lkml.sh`` (found in this repository).

6. Go on vacation for a couple of days.

7. A series of mbox files will appear in ``~/lkml-archives``.

**Uploading to Mongo.** The ``mbox2mongo.py`` script will take a collection of
mbox files and emit JSON records, one per line, suitable for importation into a
Mongo database.

1. Run this command:

    python mbox2mongo.py ~/lkml-archives/*.mbox >lkml.json

2. Use ``mongoimport`` to create a Mongo collection with the email messages:

    mongoimport -h mymongoserver -d mydatabase -c lkml --drop --file lkml.json

Be careful with the ``--drop`` option.

You may also wish to combine steps 1 and 2 into a single command that pipes the
output of ``mbox2mongo.py`` directly to ``mongoimport``.

**Processing Data.** Several scripts in the repo perform retrieval and
aggregation operations on the data stored in the Mongo server.  Following is a
brief description of what they do and how to invoke them.  All of them can be
invoked with ``mongo scriptname.js``.  The scripts engage the database by name,
so you may need to edit them to reflect your own setup.

1. `compute-first-response-time.js` is a MongoDB script that first finds the set
   of all messages that originated an email thread, then computes the earliest
   response to each of those messages, storing this value in the ``response_time``
   property of each document.

2. `compute-mean-response-time.js` is a MongoDB script that computes a new
   database collection containing mean first-response times, aggregated by
   month.  That is, the new collection contains records with keys named "month",
   "year", "mean_response_time", and "count".  This collection can be used to
   compile monthly and yearly response time stats.

3. `compute-percent-answered.js` is a MongoDB script that computes a new
   database collection containing counts of answered and unanswered
   thread-originating emails.  It has records with keys named "month", "year",
   "answered", and "unanswered".

4. `mean-response-time-to-csv.js` and `mean-response-time-to-csv-by-year.js` are
   MongoDB scripts that produce CSV formatted files containing the data in the
   computed response time collection (computed by #2).  The `by-year` variant first
   aggregates the monthly means to derive a yearly mean, giving a coarser view of
   the numbers.  You can run this script and redirect the output to a file, but
   keep in mind that MongoDB always prints an informational header whenever it is
   invoked.  You will want to use a shell utility such as ``tail`` to strip away
   these lines, or simply remember to edit the resulting file to remove the header
   manually.

5. `percent-answered-to-csv.js` and `percent-answered-to-csv-by-year.js` are
   MongoDB scripts that produce CSV formatted files containing the data in the
   computed percent answered collection (computed by #3).  The `by-year` variant
   first aggregates the monthly numbers to derive a yearly answered/unanswered
   count, giving a coarser view of the numbers.  You can run this script and
   redirect the output to a file, but keep in mind that MongoDB always prints an
   informational header whenever it is invoked.  You will want to use a shell
   utility such as ``tail`` to strip away these lines, or simply remember to edit
   the resulting file to remove the header manually.

The goal of this collection of scripts is to generate CSV files that can then be
used to produce some simple charts, such the ones you can make by importing the
files into Google docs, etc.
