CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
CLIENT_SRC = client.c
CLIENT_EXE = client
all: $(CLIENT_EXE)

$(CLIENT_EXE): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
.PHONY: clean

clean:
	rm -f $(CLIENT_EXE)
