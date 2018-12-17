#!/bin/bash
end=$((SECONDS+100));
count=0
points=0	#points in the circle
while [ $SECONDS -lt $end ]
do
        x=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
	y=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
	count=$((count+1));
	sq_x=`echo "scale=4; $x*$x" | bc -l`
	sq_y=`echo "scale=4; $y*$y" | bc -l`
	sum=`echo "$sq_x+$sq_y" | bc -l`
	sqroot=`echo "scale=4; sqrt($sum)" | bc -l`
	r=1.00
	c=$(echo "$sqroot < $r" | bc)
	if [ $c -eq 1 ]; then
	points=$(($points+1))
	fi
									
done
ratio=`echo "$points/$1" | bc -l`
pi=`echo "$ratio*4.0" | bc -l`
echo Estimated Value=  $pi
exact=`echo "22/7" | bc -l`
deviation=`echo "$pi-$exact" | bc -l`
echo Deviation= $deviation
abs=${deviation#-}
errorf=`echo "$abs/$exact" | bc -l`
errorp=`echo "$errorf*100.0" | bc -l`
echo error=$errorp"%"
echo Number of points: $count
