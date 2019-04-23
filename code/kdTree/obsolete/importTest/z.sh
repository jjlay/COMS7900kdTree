#!/bin/bash
for node in $(rocks list host | awk '{print $1}' | cut -d':' -f 1 | grep "compute")
do
	remote=`whoami`"@$node"
	echo "Checking $remote"

	cat zombiehunt.bash | ssh -t $remote 
done

