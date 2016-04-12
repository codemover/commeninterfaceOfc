GCC = gcc
CFLAG = -g

INC = -I./

target:Iptrie

Iptrie:iptrie.o main.c
	$(GCC) $(CFLAG) $(INC) -o $@  $^

iptrie.o:iptrie.c
	$(GCC) -c $<

clean:
	rm *.o Iptrie
