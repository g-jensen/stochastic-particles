all: mean resets survival_rate

mean:
	g++ -c src/*
	g++ -o mean examples/mean.cpp *.o
	rm *.o

resets:
	g++ -c src/*
	g++ -o resets examples/resets.cpp *.o
	rm *.o

survival_rate:
	g++ -c src/*
	g++ -o survival_rate examples/survival_rate.cpp *.o
	rm *.o

clean:
	rm -f *.o mean resets survival_rate