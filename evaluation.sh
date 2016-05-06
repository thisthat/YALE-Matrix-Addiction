#!/bin/bash
#prepare the env
rm *.csv
make
#run first evaluation
for i in `seq 1 10`;
do
	echo ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 0 -f strategy_0_single_thread.csv
       	 ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 0 -f strategy_0_single_thread.csv
	echo ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 1 -f strategy_1_single_thread.csv
       	 ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 1 -f strategy_1_single_thread.csv

    echo ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 2 -f strategy_2_single_thread.csv
       	 ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 2 -f strategy_2_single_thread.csv
	#echo ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 3 -f strategy_3_single_thread.csv
    #   	 ./YSFMMoltiplication -row ${i}00 -col ${i}00 -fill 5 -s 3 -f strategy_3_single_thread.csv
done

#run second evaluation
for i in `seq 2 2 80`;
do
    echo ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -s 0 -t ${i} -f strategy_0_multiple_thread.csv
         ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -s 0 -t ${i} -f strategy_0_multiple_thread.csv
    echo ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -s 1 -t ${i} -f strategy_1_multiple_thread.csv
         ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -s 1 -t ${i} -f strategy_1_multiple_thread.csv

    echo ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -s 2 -t ${i} -f strategy_2_multiple_thread.csv
         ./YSFMMoltiplication -row 1000 -col 1000 -fill 5 -s 2 -t ${i} -f strategy_2_multiple_thread.csv
    #echo ./YSFMMoltiplication -row 500 -col 500 -fill 5 -s 3 -t ${i} -f strategy_3_multiple_thread.csv
    #     ./YSFMMoltiplication -row 500 -col 500 -fill 5 -s 3 -t ${i} -f strategy_3_multiple_thread.csv
done

#run third evaluation
#j=40
#for i in `seq 1 1 10`; #run over size
#do
#    r=`echo "10^${i}" | bc`
#    echo ./YSFMMoltiplication -row ${r} -col ${r} -fill 5 -s 2 -t ${j} -f strategy_2_blow_memory.csv
#         ./YSFMMoltiplication -row ${r} -col ${r} -fill 5 -s 2 -t ${j} -f strategy_2_blow_memory.csv
    #echo ./YSFMMoltiplication -row ${r} -col ${r} -fill 5 -s 3 -t ${j} -f strategy_3_blow_memory.csv
    #     ./YSFMMoltiplication -row ${r} -col ${r} -fill 5 -s 3 -t ${j} -f strategy_3_blow_memory.csv
#done

