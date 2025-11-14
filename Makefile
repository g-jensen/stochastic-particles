all: mean resets survival_rate

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

.PHONY: gate
gate: src
	g++ -o gate examples/gate.cpp *.o

clean:
	rm -f *.o