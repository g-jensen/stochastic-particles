all: mean resets survival_rate gates wait_times

.PHONY: src
src: src/* headers/*
	g++ -c src/*

.PHONY: mean
mean: src
	g++ -o mean examples/mean.cpp *.o

.PHONY: resets
resets: src
	g++ -o resets examples/resets.cpp *.o

.PHONY: survival_rate
survival_rate: src
	g++ -o survival_rate examples/survival_rate.cpp *.o

.PHONY: gates
gates: src
	g++ -o gates examples/gates.cpp *.o

.PHONY: wait_times
wait_times: src
	g++ -o wait_times examples/wait_times.cpp *.o

clean:
	rm -f *.o