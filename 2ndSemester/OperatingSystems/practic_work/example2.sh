#!/bin/bash

if [ "$#" -lt 4 ]; then
    exit 1
fi

word=$1
m=$2
n=$3

shift 3
for file in "$@"
do
    line_n=$(sed "$nq;d" $file)
    match=$(echo "$line_n" | grep -Eo "${word}" | wc -l)

    if [ "$match" -ge "$m" ]; then
	echo "$file"
    fi
done

