#!/bin/bash

# Instances: 300, Iterations: 1500, KeepBest: 30, KeepWorst: 21, Cross: 120, MutationFactor: 0.05

rm -f .avg.dat
rm -f avg.dat
rm -f output.png 


for file in *.dat; do
	INST=$(grep "KeepBest: " $file | sed -n "s/.*KeepBest: \([0-9]*\.*[0-9]*\).*/\1/p")
	AVGTIME=$(grep "Avg. time: " $file | sed -n "s/.*Avg. time: \([0-9]*\.*[0-9]*\).*/\1/p")
	AVGFSTFEAS=$(grep "Avg. fstFeasible: " $file | sed -n "s/.*Avg. fstFeasible: \([0-9]*\.*[0-9]*\).*/\1/p")
	AVGBESTSOL=$(grep "Avg. bestSol: " $file | sed -n "s/.*Avg. bestSol: \([0-9]*\.*[0-9]*\).*/\1/p")
	echo "$INST $AVGTIME $AVGFSTFEAS $AVGBESTSOL" >> ".avg.dat"
done

sort -n .avg.dat > avg.dat

gnuplot files.plot