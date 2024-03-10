#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

int main() {
    int sockfd;
    int echo_flag=1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUF_SIZE];
    
    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind socket to server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in bind");
        exit(EXIT_FAILURE);
    }
    
    printf("Echo server is listening on %s:%d\n", SERVER_IP, SERVER_PORT);
    printf("Would you like to respond?(Y/N): ");
    fgets(buffer, BUF_SIZE, stdin);
    if (buffer[0] == 'N' && strlen(buffer) == 2 && buffer[1] == '\n') {
        echo_flag = 0;
    }
    
    // Read input from user
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        // Receive message from client
        int recv_len = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (recv_len < 0) {
            perror("Error in recvfrom");
            exit(EXIT_FAILURE);
        }else{
            printf("Echo from client: %s", buffer);
        }

        // Send the received message back to client
        if(echo_flag==0)continue;
        else if (sendto(sockfd, buffer, recv_len, 0, (struct sockaddr *)&client_addr, client_addr_len) < 0) {
            perror("Error in sendto");
            exit(EXIT_FAILURE);
        }
    }

    // Close socket
    close(sockfd);

    return 0;
}
