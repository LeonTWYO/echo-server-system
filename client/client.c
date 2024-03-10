#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/time.h>
#include <math.h> // Include the math.h header
#define BUF_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define MAX_WAIT_INTERVAL 8  // 8s in seconds
#define BASE_INTERVAL 500000        // 500ms in microseconds
#define MULTIPLIER 2

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];
    char echo_buffer[BUF_SIZE];
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
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    int recv_len;
    // Read input from user
    printf("Enter MAX_RETRY (MAX_WAIT_INTERVAL is 8s): ");
    fgets(buffer, BUF_SIZE, stdin);
    // Convert string to integer
    int MAX_RETRY = atoi(buffer);
    memset(buffer, 0, BUF_SIZE);
    printf("Enter message : ");
    fgets(buffer, BUF_SIZE, stdin);
    
    for(int retry_count=0;retry_count<=MAX_RETRY;retry_count++){
        printf("RETRY_COUNT: %d\n",retry_count);
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Error in sendto");
            exit(EXIT_FAILURE);
        }
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        recv_len = recvfrom(sockfd, echo_buffer, BUF_SIZE, 0, NULL, NULL);
        if (recv_len>0) {
            echo_buffer[recv_len] = '\0';
            break;
        }else if(retry_count<MAX_RETRY){
            int powerTwo = MULTIPLIER << retry_count;
            int wait_interval;
            if(powerTwo>16) 
                wait_interval=MAX_WAIT_INTERVAL;
            else    
                wait_interval=BASE_INTERVAL*powerTwo/1000000;
            printf("wait_interval: %d\n",wait_interval);
            sleep(wait_interval);
        }
    }
    if(recv_len>0){
        printf("Echo from server: %s\n", echo_buffer); 
        exit(0); // Exit program with code 0 after receiving echo message
    }else{
        printf("No echo message received within max retry limit.\n");
        exit(1); // Exit program with code 1 if max retry is reached
    }

    // Close socket
    close(sockfd);

    return 0;
}
