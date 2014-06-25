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

**Processing data.** The ``mbox2mongo.py`` script will take a collection of mbox
files and emit JSON records, one per line, suitable for importation into a Mongo
database.

1. Run this command:

    python mbox2mongo.py ~/lkml-archives/*.mbox >lkml.json

2. Use ``mongoimport`` to create a Mongo collection with the email messages:

    mongoimport -h mymongoserver -d mydatabase -c lkml --drop --file lkml.json

Be careful with the ``--drop`` option.

You may also wish to combine steps 1 and 2 into a single command that pipes the
output of ``mbox2mongo.py`` directly to ``mongoimport``.
