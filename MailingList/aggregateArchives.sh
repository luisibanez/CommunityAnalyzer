#!/bin/bash

#
#  This script is to be used after calling
#
#        ./downloadArchives.sh
#

#
#  Decompress all the files
#
gunzip   *.txt.gz

#
#  Aggregate them into a single file
#
cat 20*.txt  >  ITKUsers.txt

