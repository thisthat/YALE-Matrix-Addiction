#!/bin/bash
#prepare the env
rm *.csv
make
#run first evaluation
for i in `seq 1 10`;
do
	  echo ./YSFMAddiction -row ${i}000 -col ${i}000 -fill 5 -s 0 -f strategy_0_single_thread.csv
         ./YSFMAddiction -row ${i}000 -col ${i}000 -fill 5 -s 0 -f strategy_0_single_thread.csv
	  echo ./YSFMAddiction -row ${i}000 -col ${i}000 -fill 5 -s 1 -f strategy_1_single_thread.csv
         ./YSFMAddiction -row ${i}000 -col ${i}000 -fill 5 -s 1 -f strategy_1_single_thread.csv

    echo ./YSFMAddiction -row ${i}000 -col ${i}000 -fill 5 -s 2 -f strategy_2_single_thread.csv
       	 ./YSFMAddiction -row ${i}000 -col ${i}000 -fill 5 -s 2 -f strategy_2_single_thread.csv
   	echo ./YSFMAddiction -row ${i}000 -col ${i}000 -fill 5 -s 3 -f strategy_3_single_thread.csv
       	 ./YSFMAddiction -row ${i}000 -col ${i}000 -fill 5 -s 3 -f strategy_3_single_thread.csv 
done

#run second evaluation
size=3000
for i in `seq 2 2 80`;
do
    echo ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 0 -t ${i} -f strategy_0_multiple_thread.csv
         ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 0 -t ${i} -f strategy_0_multiple_thread.csv
    echo ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 1 -t ${i} -f strategy_1_multiple_thread.csv
         ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 1 -t ${i} -f strategy_1_multiple_thread.csv

    echo ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 2 -t ${i} -f strategy_2_multiple_thread.csv
         ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 2 -t ${i} -f strategy_2_multiple_thread.csv
    echo ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 3 -t ${i} -f strategy_3_multiple_thread.csv
         ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 3 -t ${i} -f strategy_3_multiple_thread.csv
done

#run third evaluation
size=15000
for i in `seq 2 2 80`;
do
    echo ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 3 -t ${i} -f strategy_3_init.csv
         ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 3 -t ${i} -f strategy_3_init.csv
    echo ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 1 -t ${i} -f strategy_1_init.csv
         ./YSFMAddiction -row ${size} -col ${size} -fill 5 -s 1 -t ${i} -f strategy_1_init.csv
done

