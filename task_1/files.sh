#!/bin/bash

ID=( $(cat output.txt | grep -i "input" | grep -Po "\d+") )
MERR=( $(cat output.txt | grep -i "max_err" | grep -Po "\d+.\d+") )
AERR=( $(cat output.txt | grep -i "avg_err" | grep -Po "\d+.\d+") )
TOPTTIME=( $(cat output.txt | grep -i "total_time_opt" | grep -Po "\d+.\d+") )
TAPXTIME=( $(cat output.txt | grep -i "total_time_apx" | grep -Po "\d+.\d+") )

rm -f max_err.txt
rm -f avg_err.txt
rm -f optimal_time.txt
rm -f approx_time.txt

LEN=${#ID[@]}
for (( c=0; c<$LEN; c++ )); do
	echo "${ID[${c}]}	${MERR[${c}]}" >> "max_err.txt";
done

for (( c=0; c<$LEN; c++ )); do
	echo "${ID[${c}]}	${AERR[${c}]}" >> "avg_err.txt";
done

for (( c=0; c<$LEN; c++ )); do
	echo "${ID[${c}]}	${TOPTTIME[${c}]}" >> "optimal_time.txt";
done

for (( c=0; c<$LEN; c++ )); do
	echo "${ID[${c}]}	${TAPXTIME[${c}]}" >> "approx_time.txt";
done