.SILENT:

all: main

lib:
	make -C ../measure/

main: lib main.cpp
	g++ main.cpp -L../measure -I../measure -l:libmeasure.a -o main

run: main
	sudo taskset -c 1 ./main imul 2> imul.csv
	sudo taskset -c 1 ./main add 2> add.csv
	sudo taskset -c 1 ./main nop 2> nop.csv
	sudo taskset -c 1 ./main clflush 2> clflush.csv
	sudo taskset -c 1 ./main inc 2> inc.csv
	sudo taskset -c 1 ./main xor 2> xor.csv
	sudo taskset -c 1 ./main mov 2> mov.csv
	sudo taskset -c 1 ./main fscale 2> fscale.csv
	sudo taskset -c 1 ./main rdtsc 2> rdtsc.csv
	# 	sudo taskset -c 1 ./main rdrand 2> rdrand.csv

plot:
	python3 plot.py clflush.csv mov.csv fscale.csv rdtsc.csv imul.csv add.csv nop.csv inc.csv xor.csv

clean:
	make -C ../measure/ clean
	rm -r main imul.csv add.csv nop.csv clflush.csv inc.csv xor.csv mov.csv fscale.csv rdtsc.csv
