HashTable: hashtable.o date.o
	g++ -o HashTable hashtable.o date.o

hashtable.o: hashtable.cpp
	g++ -c hashtable.cpp

date.o: date.cpp
	g++ -c date.cpp

clean:
	rm HashTable *.o *.gch *.stackdump
