#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "ERROR"
    exit 1
fi

word=$1

shift 1
for file in "$@"
do
    count=$(echo "$file" | grep -Eo "${word}" | wc -m)
    echo $count
done


