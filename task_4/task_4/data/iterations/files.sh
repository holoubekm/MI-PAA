#!/bin/bash

# Instances: 300, Iterations: 1500, KeepBest: 30, KeepWorst: 21, Cross: 120, MutationFactor: 0.05

rm -f .avg_time.dat
rm -f avg_time.dat
rm -f .avg_err.dat
rm -f avg_err.dat
rm -f output.png 

for file in *.dat; do
	ITERS=$(grep "Iterations: " $file | sed -n "s/.*Iterations: \([0-9]*\.*[0-9]*\).*/\1/p")
	AVGTIME=$(grep "Avg. time: " $file | sed -n "s/.*Avg. time: \([0-9]*\.*[0-9]*\).*/\1/p")
	AVGERR=$(grep "Total avg. error: " $file | sed -n "s/.*Total avg. error: \([0-9]*\.*[0-9]*\).*/\1/p")
	echo "$ITERS $AVGTIME" >> ".avg_time.dat"
	echo "$ITERS $AVGERR" >> ".avg_err.dat"
done

sort -n .avg_time.dat > avg_time.dat
sort -n .avg_err.dat > avg_err.dat

gnuplot files.plot