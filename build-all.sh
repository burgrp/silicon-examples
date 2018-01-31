#!/bin/sh

set -e

for dir in *
do
	if [ -e $dir/package.json ] && [ -e $dir/app.cpp ]
	then
		echo "Building $dir"
		silicon -c $dir build -sd
	fi
done
