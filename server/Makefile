CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
SERVER_SRC = server.c
SERVER_EXE = server

all:    $(SERVER_EXE)

$(SERVER_EXE): $(SERVER_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(SERVER_EXE)
