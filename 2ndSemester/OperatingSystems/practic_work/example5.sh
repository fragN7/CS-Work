#!/bin/bash

if [ "$#" -lt 3 ];then
    echo "Error"
    exit 1
fi

number=$1
word=$2

shift 2

for file in "$@"
do
    line_number=0
    for line in "$file"
    do
	if [ echo "$line" | grep -Eq "${word}" ];then
	    line_number=$($line_number + 1)
	fi
	if [ $line_number==$number ];then
	    echo $line
	fi
    done
done

for file in "$@"
do
    lines=$(cat "$file" | grep -E "${w}")
    nthline=$(echo "$lines" | tail -n +"$n" | head -n 1)

    echo "$nthline"
done
