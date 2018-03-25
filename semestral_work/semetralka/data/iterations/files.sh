#!/bin/bash

rm -f .avg.dat
rm -f avg.dat
rm -f output.png 


for file in *.dat; do
	ITERS=$(grep "Iterations: " $file | sed -n "s/.*Iterations: \([0-9]*\.*[0-9]*\).*/\1/p")
	AVGTIME=$(grep "Avg. time: " $file | sed -n "s/.*Avg. time: \([0-9]*\.*[0-9]*\).*/\1/p")
	AVGFSTFEAS=$(grep "Avg. fstFeasible: " $file | sed -n "s/.*Avg. fstFeasible: \([0-9]*\.*[0-9]*\).*/\1/p")
	AVGBESTSOL=$(grep "Avg. bestSol: " $file | sed -n "s/.*Avg. bestSol: \([0-9]*\.*[0-9]*\).*/\1/p")
	echo "$ITERS $AVGTIME $AVGFSTFEAS $AVGBESTSOL" >> ".avg.dat"
done

sort -n .avg.dat > avg.dat

gnuplot files.plot