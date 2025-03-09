#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>



int main() {
    int sockfd;
    char buffer[2000];
    struct sockaddr_in server, client;
    socklen_t c = sizeof(client);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind the socket
    if (bind(sockfd, (const struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Echo Server listening on port %d...\n", 8888);

    while (1) {
        // Receive message from client
        int n = recvfrom(sockfd, buffer, 2000, 0, (struct sockaddr *)&client, &c);
        buffer[n] = '\0';
        printf("Received: %s\n", buffer);

        // Echo message back to client
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client, c);
        printf("Echoed back to client\n");
    }

    close(sockfd);
    return 0;
}
