#!/bin/bash
#prepare the env
rm *.csv
make
#run first simulation
for i in `seq 1 10`;
do
	echo ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 0 -f strategy_0_single.csv
       	./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 0 -f strategy_0_single.csv
	echo ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 1 -f strategy_1_single.csv
       	./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 1 -f strategy_1_single.csv
done  
#run second
for i in `seq 1 10`;
do
        echo ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -t ${i} -s 0 -f strategy_0_single.csv
        ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -s 0 -t ${i} -f strategy_0_single.csv
        echo ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -t $(i} -s 1 -f strategy_1_single.csv
        ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -s 1 -t ${i} -f strategy_1_single.csv
done
