CC = g++
CCFLAGS = -g

Bvector : main.o Bvector.o Avector.o Kvector.o
	$(CC) $(CCFLAGS) -o Bvector main.o Bvector.o Avector.o Kvector.o

BitSet: BitSet.o Bvector.o Kvector.o
	$(CC) $(CCFLAGS) -o BitSet BitSet.o Bvector.o Kvector.o

clean:
	rm -f *.0

%.o : %.cpp %.h
	$(CC) $(CCFLAGS) -c $<

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $<

% : %.cpp
	$(CC) $(CCFLAGS) -o $@ $<
