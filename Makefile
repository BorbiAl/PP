CC = gcc
CFLAGS = -Wall -std=c11

all:
	$(CC) $(CFLAGS) -o bank main.c auth/auth.c operations/operations.c

clean:
	rm -f bank bank.exe
