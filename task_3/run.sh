#!/bin/bash

# rm -rf output
# mkdir output 

# for file in ./knapgen/ratio/*; do
# 	./task_4 "$file" >> output/ratio.dat
# done

# for file in ./knapgen/maxweight/*; do
# 	./task_4 "$file" >> output/maxweight.dat
# done

# for file in ./knapgen/maxcost/*; do
# 	./task_4 "$file" >> output/maxcost.dat
# done

# for file in ./knapgen/gran_small/*; do
# 	./task_4 "$file" >> output/gran_small.dat
# done

# for file in ./knapgen/gran_big/*; do
# 	./task_4 "$file" >> output/gran_big.dat
# done

cd output

# EXP_BIG=( $(grep input gran_big.dat | sed -re "s/.*exponent_([0-9]_[0-9]*).dat/\1/" | tr '_' '.') )
# AVG_ERR_RATIO=( $(grep avg_err gran_big.dat | sed -re "s/^avg_err: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_RATIO=( $(grep avg_time_ratio gran_big.dat | sed -re "s/^avg_time_ratio: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_BB=( $(grep avg_time_bb gran_big.dat | sed -re "s/^avg_time_bb: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_DYN=( $(grep avg_time_dyn gran_big.dat | sed -re "s/^avg_time_dyn: ([0-9].[0-9]*)/\1/") )

# echo "Exponent granularity	Prům. čas (s) - větve a hranice	Prům. čas (s) - dyn. prog.	Prům. čas (s) - apx. řešení	Prům. rel. chyba (%) apx. řeš" > gran_big.out.txt
# LEN=${#EXP_BIG[@]}
# for (( c=0; c<$LEN; c++ )); do
# 	echo -e "${EXP_BIG[${c}]}	${AVG_TIME_BB[${c}]}	${AVG_TIME_DYN[${c}]}	${AVG_TIME_RATIO[${c}]}	${AVG_ERR_RATIO[${c}]}" >> gran_big.out.txt;
# done


# EXP_SML=( $(grep input gran_small.dat | sed -re "s/.*exponent_([0-9]_[0-9]*).dat/\1/" | tr '_' '.') )
# AVG_ERR_RATIO=( $(grep avg_err gran_small.dat | sed -re "s/^avg_err: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_RATIO=( $(grep avg_time_ratio gran_small.dat | sed -re "s/^avg_time_ratio: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_BB=( $(grep avg_time_bb gran_small.dat | sed -re "s/^avg_time_bb: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_DYN=( $(grep avg_time_dyn gran_small.dat | sed -re "s/^avg_time_dyn: ([0-9].[0-9]*)/\1/") )

# echo "Exponent granularity	Prům. čas (s) - větve a hranice	Prům. čas (s) - dyn. prog.	Prům. čas (s) - apx. řešení	Prům. rel. chyba (%) apx. řeš" > gran_sml.out.txt
# LEN=${#EXP_SML[@]}
# for (( c=0; c<$LEN; c++ )); do
# 	echo -e "${EXP_SML[${c}]}	${AVG_TIME_BB[${c}]}	${AVG_TIME_DYN[${c}]}	${AVG_TIME_RATIO[${c}]}	${AVG_ERR_RATIO[${c}]}" >> gran_sml.out.txt;
# done

# MAXCOST=( $(grep input maxcost.dat | sed -re "s/.*max_cost_([0-9]*).dat/\1/" | tr '_' '.') )
# AVG_ERR_RATIO=( $(grep avg_err maxcost.dat | sed -re "s/^avg_err: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_RATIO=( $(grep avg_time_ratio maxcost.dat | sed -re "s/^avg_time_ratio: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_BB=( $(grep avg_time_bb maxcost.dat | sed -re "s/^avg_time_bb: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_DYN=( $(grep avg_time_dyn maxcost.dat | sed -re "s/^avg_time_dyn: ([0-9].[0-9]*)/\1/") )

# echo "Maximální cena	Prům. čas (s) - větve a hranice	Prům. čas (s) - dyn. prog.	Prům. čas (s) - apx. řešení	Prům. rel. chyba (%) apx. řeš" > maxcost.out.txt
# LEN=${#EXP_SML[@]}
# for (( c=0; c<$LEN; c++ )); do
# 	echo -e "${MAXCOST[${c}]}	${AVG_TIME_BB[${c}]}	${AVG_TIME_DYN[${c}]}	${AVG_TIME_RATIO[${c}]}	${AVG_ERR_RATIO[${c}]}" >> maxcost.out.txt;
# done

# MAXWEIGHT=( $(grep input maxweight.dat | sed -re "s/.*max_weight_([0-9]*).dat/\1/" | tr '_' '.') )
# AVG_ERR_RATIO=( $(grep avg_err maxweight.dat | sed -re "s/^avg_err: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_RATIO=( $(grep avg_time_ratio maxweight.dat | sed -re "s/^avg_time_ratio: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_BB=( $(grep avg_time_bb maxweight.dat | sed -re "s/^avg_time_bb: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_DYN=( $(grep avg_time_dyn maxweight.dat | sed -re "s/^avg_time_dyn: ([0-9].[0-9]*)/\1/") )

# echo "Maximální váha	Prům. čas (s) - větve a hranice	Prům. čas (s) - dyn. prog.	Prům. čas (s) - apx. řešení	Prům. rel. chyba (%) apx. řeš" > maxweight.out.txt
# LEN=${#EXP_SML[@]}
# for (( c=0; c<$LEN; c++ )); do
# 	echo -e "${MAXWEIGHT[${c}]}	${AVG_TIME_BB[${c}]}	${AVG_TIME_DYN[${c}]}	${AVG_TIME_RATIO[${c}]}	${AVG_ERR_RATIO[${c}]}" >> maxweight.out.txt;
# done



# RATIO=( $(grep input ratio.dat | sed -re "s/.*ratio_([0-9]_[0-9]*).dat/\1/" | tr '_' '.') )
# AVG_ERR_RATIO=( $(grep avg_err ratio.dat | sed -re "s/^avg_err: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_RATIO=( $(grep avg_time_ratio ratio.dat | sed -re "s/^avg_time_ratio: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_BB=( $(grep avg_time_bb ratio.dat | sed -re "s/^avg_time_bb: ([0-9].[0-9]*)/\1/") )
# AVG_TIME_DYN=( $(grep avg_time_dyn ratio.dat | sed -re "s/^avg_time_dyn: ([0-9].[0-9]*)/\1/") )

# echo "Poměr sum. ceny a kapacity	Prům. čas (s) - větve a hranice	Prům. čas (s) - dyn. prog.	Prům. čas (s) - apx. řešení	Prům. rel. chyba (%) apx. řeš" > ratio.out.txt
# LEN=${#EXP_SML[@]}
# for (( c=0; c<$LEN; c++ )); do
# 	echo -e "${RATIO[${c}]}	${AVG_TIME_BB[${c}]}	${AVG_TIME_DYN[${c}]}	${AVG_TIME_RATIO[${c}]}	${AVG_ERR_RATIO[${c}]}" >> ratio.out.txt;
# done


cat gran_big.out.txt | sort -n > .gran_big.out.txt
cat gran_sml.out.txt | sort -n > .gran_sml.out.txt
cat maxcost.out.txt | sort -n > .maxcost.out.txt
cat maxweight.out.txt | sort -n > .maxweight.out.txt
cat ratio.out.txt | sort -n > .ratio.out.txt

mv .gran_big.out.txt gran_big.out.txt
mv .gran_sml.out.txt gran_sml.out.txt
mv .maxcost.out.txt maxcost.out.txt
mv .maxweight.out.txt maxweight.out.txt
mv .ratio.out.txt ratio.out.txt

cd ../

gnuplot gran_big.plot
gnuplot gran_sml.plot
gnuplot maxcost.plot
gnuplot maxweight.plot
gnuplot ratio.plot