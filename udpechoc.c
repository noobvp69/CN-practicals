#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    char buffer[2000];
    struct sockaddr_in server;
    socklen_t c = sizeof(server);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Enter message: ");
        fgets(buffer, 2000, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        // Send message to server
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, c);

        // Receive response from server
        int n = recvfrom(sockfd, buffer, 2000, 0, (struct sockaddr *)&server, &c);
        buffer[n] = '\0';

        printf("Server echoed: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
