#!/bin/bash

baseurl=http://www.itk.org/pipermail/insight-users/

months=( January February March April May June July August September October November December )

startyear=2000
endyear=2014

year=$startyear

while [[ $year -le $endyear ]]
do
  echo "$year"
  ((year=year+1))
  for month in "${months[@]}"
  do
    filename=$baseurl$year'-'$month'.txt.gz'
    echo "$filename"
    wget -c "${filename}"
  done
done

