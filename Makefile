

all: Money

Money: md5.o Money.o
	g++ md5.o Money.o -o Money

md5.o: md5.cpp
	g++ -c md5.cpp

Money.o: Money.cpp
	g++ -c Money.cpp

clean:
	rm *o Money