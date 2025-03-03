#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 8888
#define BUF_SIZE 2000

int main() {
    int sockdes, b;
    FILE *fd;
    char s[100] = "";
    char s2[25] = "";
    char s1[BUF_SIZE] = "";
    struct sockaddr_in server;

    // Create UDP socket
    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes < 0) {
        perror("Cannot create socket");
        return 1;
    }

    // Set up server address (use the server's IP address)
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Replace with the server's IP address
    server.sin_port = htons(PORT);                     // Server port

    printf("\nEnter the file name: ");
    scanf("%s", s);
    printf("\nEnter the new file name: ");
    scanf("%s", s2);

    // Send the requested file name to the server
    sendto(sockdes, s, strlen(s), 0, (struct sockaddr *)&server, sizeof(server));
    printf("Sent request for file: %s\n", s);

    // Open the file to write the received data
    fd = fopen(s2, "wb");  // Open in binary mode
    if (fd == NULL) {
        perror("Failed to open file for writing");
        close(sockdes);
        return 1;
    }

    // Receive file content from server
    while ((b = recvfrom(sockdes, s1, sizeof(s1), 0, NULL, NULL)) > 0) {
        // Check if the end-of-file signal is received
        if (strncmp(s1, "END_OF_FILE", 11) == 0) {
            printf("\nEnd of file transfer\n");
            break;
        }

        printf("Received %d bytes\n", b);  // Debugging received bytes
        fwrite(s1, 1, b, fd);  // Write the received data into the file
    }

    printf("\nFile received successfully\n");

    // Close file and socket
    fclose(fd);
    close(sockdes);

    return 0;
}

