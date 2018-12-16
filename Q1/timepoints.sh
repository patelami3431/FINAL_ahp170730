#!/bin/bash
end=$((SECONDS+100));
count=0
while [ $SECONDS -lt $end ]
do
        x=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
	y=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
	count=$((count+1));
done
echo $count
