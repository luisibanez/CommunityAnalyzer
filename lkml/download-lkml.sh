#!/bin/sh

start=1
total=1700000
chunk=1000

for i in `seq $start $chunk $total`; do
    j=$(($i + $chunk))
    label=`printf "%07d" $j`
    echo "Retrieving emails $i through $j"
    curl http://download.gmane.org/gmane.linux.kernel/$i/$j >lkml.$label.mbox
done
