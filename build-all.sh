#!/bin/sh

set -e

for dir in *
do
	if [ -e $dir/package.json ]
	then
		echo "Building $dir"
		silicon -c $dir build -s
	fi
done
