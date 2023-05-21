#!/bin/bash

if [ "$#" -lt 2 ];then
    echo "Error"
    exit 1
fi

number=$1
libs=""
shift 1

for file in "$@"
do
   while IFS= read -r line
   do
      if echo "$file" | grep -Eq ^'#include'; then
       	  libs="${libs}${line}"$'\n'
      fi
   done < $file
done

result=$(echo "${libs::-1}" | sort | uniq -c | sort -n -r -k 1,1 | head -n $number)
echo "$result"
