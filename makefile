CC = g++
CFLAGS = TG20181.cpp


all: comp exec clean

comp: 
	$(CC) $(CFLAGS) -o exe 

exec:
	./exe < entradas.txt
	

.PHONY: clean

clean: 
	rm -f exe
