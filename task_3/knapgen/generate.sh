#!/bin/bash


#Ratio
rm -rf ratio
mkdir ratio
echo "-n 50 -N 50 -m 0.1 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_1.dat
echo "-n 50 -N 50 -m 0.2 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_2.dat
echo "-n 50 -N 50 -m 0.3 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_3.dat
echo "-n 50 -N 50 -m 0.4 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_4.dat
echo "-n 50 -N 50 -m 0.5 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_5.dat
echo "-n 50 -N 50 -m 0.6 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_6.dat
echo "-n 50 -N 50 -m 0.7 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_7.dat
echo "-n 50 -N 50 -m 0.8 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_8.dat
echo "-n 50 -N 50 -m 0.9 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_0_9.dat
echo "-n 50 -N 50 -m 1.0 -W 200 -C 100 -k 1 -d 0" > ./ratio/knap_ratio_1_0.dat

./knapgen -n 50 -N 50 -m 0.1 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_1.dat
./knapgen -n 50 -N 50 -m 0.2 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_2.dat
./knapgen -n 50 -N 50 -m 0.3 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_3.dat
./knapgen -n 50 -N 50 -m 0.4 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_4.dat
./knapgen -n 50 -N 50 -m 0.5 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_5.dat
./knapgen -n 50 -N 50 -m 0.6 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_6.dat
./knapgen -n 50 -N 50 -m 0.7 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_7.dat
./knapgen -n 50 -N 50 -m 0.8 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_8.dat
./knapgen -n 50 -N 50 -m 0.9 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_0_9.dat
./knapgen -n 50 -N 50 -m 1.0 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./ratio/knap_ratio_1_0.dat



#MaxWeight
rm -rf maxweight
mkdir maxweight
echo "-n 50 -N 50 -m 0.8 -W  75 -C 100 -k 1 -d 0" >  ./maxweight/knap_max_weight_75.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_100.dat
echo "-n 50 -N 50 -m 0.8 -W 125 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_125.dat
echo "-n 50 -N 50 -m 0.8 -W 150 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_150.dat
echo "-n 50 -N 50 -m 0.8 -W 175 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_175.dat
echo "-n 50 -N 50 -m 0.8 -W 200 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_200.dat
echo "-n 50 -N 50 -m 0.8 -W 225 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_225.dat
echo "-n 50 -N 50 -m 0.8 -W 250 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_250.dat
echo "-n 50 -N 50 -m 0.8 -W 275 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_275.dat
echo "-n 50 -N 50 -m 0.8 -W 300 -C 100 -k 1 -d 0" > ./maxweight/knap_max_weight_300.dat

./knapgen -n 50 -N 50 -m 0.8 -W  75 -C 100 -k 1 -d 0 2>/dev/null >>  ./maxweight/knap_max_weight_75.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_100.dat
./knapgen -n 50 -N 50 -m 0.8 -W 125 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_125.dat
./knapgen -n 50 -N 50 -m 0.8 -W 150 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_150.dat
./knapgen -n 50 -N 50 -m 0.8 -W 175 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_175.dat
./knapgen -n 50 -N 50 -m 0.8 -W 200 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_200.dat
./knapgen -n 50 -N 50 -m 0.8 -W 225 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_225.dat
./knapgen -n 50 -N 50 -m 0.8 -W 250 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_250.dat
./knapgen -n 50 -N 50 -m 0.8 -W 275 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_275.dat
./knapgen -n 50 -N 50 -m 0.8 -W 300 -C 100 -k 1 -d 0 2>/dev/null >> ./maxweight/knap_max_weight_300.dat


#MaxCost
rm -rf maxcost
mkdir maxcost
echo "-n 50 -N 50 -m 0.8 -W 100 -C  5 -k 1 -d 0" > ./maxcost/knap_max_cost_5.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 10 -k 1 -d 0" > ./maxcost/knap_max_cost_10.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 15 -k 1 -d 0" > ./maxcost/knap_max_cost_15.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 20 -k 1 -d 0" > ./maxcost/knap_max_cost_20.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 25 -k 1 -d 0" > ./maxcost/knap_max_cost_25.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 30 -k 1 -d 0" > ./maxcost/knap_max_cost_30.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 35 -k 1 -d 0" > ./maxcost/knap_max_cost_35.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 40 -k 1 -d 0" > ./maxcost/knap_max_cost_40.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 45 -k 1 -d 0" > ./maxcost/knap_max_cost_45.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 50 -k 1 -d 0" > ./maxcost/knap_max_cost_50.dat

./knapgen -n 50 -N 50 -m 0.8 -W 100 -C  5 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_5.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 10 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_10.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 15 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_15.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 20 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_20.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 25 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_25.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 30 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_30.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 35 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_35.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 40 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_40.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 45 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_45.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 50 -k 1 -d 0 2>/dev/null >> ./maxcost/knap_max_cost_50.dat


#Granularity small
rm -rf gran_small
mkdir gran_small
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 0.50 -d -1" > ./gran_small/knap_exponent_0_50.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 0.75 -d -1" > ./gran_small/knap_exponent_0_75.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.00 -d -1" > ./gran_small/knap_exponent_1_00.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.25 -d -1" > ./gran_small/knap_exponent_1_25.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.50 -d -1" > ./gran_small/knap_exponent_1_50.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.75 -d -1" > ./gran_small/knap_exponent_1_75.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.00 -d -1" > ./gran_small/knap_exponent_2_00.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.25 -d -1" > ./gran_small/knap_exponent_2_25.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.50 -d -1" > ./gran_small/knap_exponent_2_50.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.75 -d -1" > ./gran_small/knap_exponent_2_75.dat

./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 0.50 -d -1 2>/dev/null >> ./gran_small/knap_exponent_0_50.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 0.75 -d -1 2>/dev/null >> ./gran_small/knap_exponent_0_75.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.00 -d -1 2>/dev/null >> ./gran_small/knap_exponent_1_00.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.25 -d -1 2>/dev/null >> ./gran_small/knap_exponent_1_25.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.50 -d -1 2>/dev/null >> ./gran_small/knap_exponent_1_50.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.75 -d -1 2>/dev/null >> ./gran_small/knap_exponent_1_75.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.00 -d -1 2>/dev/null >> ./gran_small/knap_exponent_2_00.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.25 -d -1 2>/dev/null >> ./gran_small/knap_exponent_2_25.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.50 -d -1 2>/dev/null >> ./gran_small/knap_exponent_2_50.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.75 -d -1 2>/dev/null >> ./gran_small/knap_exponent_2_75.dat

#Granularity big
rm -rf gran_big
mkdir gran_big
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 0.50 -d 1" > ./gran_big/knap_exponent_0_50.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 0.75 -d 1" > ./gran_big/knap_exponent_0_75.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.00 -d 1" > ./gran_big/knap_exponent_1_00.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.25 -d 1" > ./gran_big/knap_exponent_1_25.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.50 -d 1" > ./gran_big/knap_exponent_1_50.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.75 -d 1" > ./gran_big/knap_exponent_1_75.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.00 -d 1" > ./gran_big/knap_exponent_2_00.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.25 -d 1" > ./gran_big/knap_exponent_2_25.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.50 -d 1" > ./gran_big/knap_exponent_2_50.dat
echo "-n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.75 -d 1" > ./gran_big/knap_exponent_2_75.dat

./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 0.50 -d 1 2>/dev/null >> ./gran_big/knap_exponent_0_50.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 0.75 -d 1 2>/dev/null >> ./gran_big/knap_exponent_0_75.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.00 -d 1 2>/dev/null >> ./gran_big/knap_exponent_1_00.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.25 -d 1 2>/dev/null >> ./gran_big/knap_exponent_1_25.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.50 -d 1 2>/dev/null >> ./gran_big/knap_exponent_1_50.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 1.75 -d 1 2>/dev/null >> ./gran_big/knap_exponent_1_75.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.00 -d 1 2>/dev/null >> ./gran_big/knap_exponent_2_00.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.25 -d 1 2>/dev/null >> ./gran_big/knap_exponent_2_25.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.50 -d 1 2>/dev/null >> ./gran_big/knap_exponent_2_50.dat
./knapgen -n 50 -N 50 -m 0.8 -W 100 -C 100 -k 2.75 -d 1 2>/dev/null >> ./gran_big/knap_exponent_2_75.dat

	# -I	ne	celé číslo	Počáteční ID
	# -n	ano	celé číslo	počet věcí
	# -N	ano	celé číslo	počet instancí
	# -m	<0, 1> ano	reálné číslo	poměr kapacity batohu k sumární váze
	# -W	ano	celé číslo	max. váha věci
	# -C	ano	celé číslo	max. cena věci
	# -k	ano	reálné číslo	exponent k
	# -d	ano	-1, 0, 1	-1..více malých věcí, 1..více velkých věcí, 0..rovnováha


	# maximální váze věcí
	# maximální ceně věcí
	# poměru kapacity batohu k sumární váze
	# granularitě (pozor - zde si uvědomte smysl exponentu granularity)
