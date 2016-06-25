CC = gcc
CFLAG = -g -lpthread

INC = -I./

target:queue

queue:logqueue.o main.c
	$(CC) $(CFLAG) $(INC) -o $@ $^

logqueue.o:logqueue.c
	$(CC) -c $<

clean:
	rm *.o queue -f
