# echo-server-system
# Client and Server Programs README

## Client Program

### Overview
This client program is designed to send a message to a server via UDP (User Datagram Protocol) and wait for an echo response. It implements a retry mechanism with exponential backoff in case the initial attempt fails to receive a response from the server. The program allows users to specify the maximum number of retry attempts and the message to be sent.

### Requirements
- This program is written in C and requires a C compiler to build and run.
- It uses the following standard C libraries:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`
  - `unistd.h`
  - `arpa/inet.h`
  - `errno.h`
  - `sys/time.h`
  - `math.h`

### Compilation
To compile the program, use the following command:

### Usage
After compiling the program, execute the binary file `client` with the following command:
Upon execution, the program prompts the user to enter the maximum number of retry attempts (`MAX_RETRY`) and the message to be sent to the server. The user should input the desired values as prompted.

### Program Logic
1. The program establishes a UDP socket and initializes the server address.
2. It prompts the user to enter the `MAX_RETRY` value and the message to be sent.
3. The program enters a retry loop, attempting to send the message to the server.
4. Each retry attempt uses an exponential backoff strategy, where the wait interval between retries increases exponentially.
5. If a response is received from the server within the maximum retry attempts, the program prints the echoed message and exits with code 0.
6. If no response is received within the maximum retry attempts, the program prints an error message and exits with code 1.

### Configuration Parameters
- `BUF_SIZE`: Maximum buffer size for sending and receiving messages.
- `SERVER_IP`: IP address of the server.
- `SERVER_PORT`: Port number of the server.
- `MAX_WAIT_INTERVAL`: Maximum wait interval between retries (8 seconds).
- `BASE_INTERVAL`: Initial wait interval between retries (500 milliseconds).
- `MULTIPLIER`: Multiplier used for exponential backoff calculation.

### Notes
- Ensure that the server is running and listening on the specified IP address and port before running the client program.
- Adjust the `BASE_INTERVAL`, `MULTIPLIER`, and `MAX_RETRY` values according to your specific requirements.
- This program does not handle scenarios such as network errors or server unavailability beyond retry attempts.

## Server Program

### Overview
This server program listens for incoming UDP messages from clients, echoes the received messages back to the clients, and provides an option to disable echoing if required. It runs indefinitely, continuously listening for incoming messages.

### Requirements
- This program is written in C and requires a C compiler to build and run.
- It uses the following standard C libraries:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`
  - `unistd.h`
  - `arpa/inet.h`

### Compilation
To compile the program, use the following command:

### Usage
After compiling the program, execute the binary file `server` with the following command:
Upon execution, the program prompts the user to specify whether to respond to client messages by entering 'Y' for yes or 'N' for no. Once the server is running, it continuously listens for incoming messages.

### Program Logic
1. The program establishes a UDP socket and binds it to the specified IP address and port.
2. It listens for incoming messages from clients.
3. Upon receiving a message, it echoes the message back to the client if the echo option is enabled.
4. The program runs indefinitely, continuously listening for incoming messages.

### Configuration Parameters
- `BUF_SIZE`: Maximum buffer size for sending and receiving messages.
- `SERVER_IP`: IP address of the server.
- `SERVER_PORT`: Port number of the server.

### Notes
- Ensure that the client sends messages to the correct IP address and port where the server is listening.
- This program does not handle scenarios such as multiple clients or network errors.

