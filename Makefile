all: mean resets survival_rate

src: src/*
	g++ -c src/*

mean: src
	g++ -o mean examples/mean.cpp *.o

resets: src
	g++ -o resets examples/resets.cpp *.o

survival_rate: src
	g++ -o survival_rate examples/survival_rate.cpp *.o

clean:
	rm -f *.o