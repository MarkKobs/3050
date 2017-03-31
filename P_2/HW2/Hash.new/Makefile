OBJS = main.o hashtable.o  
CC = gcc  
CFLAGS = -Wall -O -g 

helloworld : $(OBJS)  
	$(CC) $(OBJS) -o helloworld  

main.o : main.c hashtable.h  
	$(CC) $(CFLAGS) -c main.c -o main.o  

hashtable.o : hashtable.c hashtable.h  
	$(CC) $(CFLAGS) -c hashtable.c -o hashtable.o  

clean:  
	rm -rf *.o helloworld
