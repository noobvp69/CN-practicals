#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 8888
#define BUF_SIZE 2000

int main() {
    int sockdes, fd, bytesRead;
    char fname[25] = "";
    char fcontent[BUF_SIZE] = "";
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);

    // Create UDP socket
    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes < 0) {
        perror("Cannot create socket");
        return 1;
    }

    // Set up server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // Accept connections on any IP address
    server.sin_port = htons(PORT);       // Server port

    // Bind socket to the address
    if (bind(sockdes, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }
    printf("Server is listening on port %d...\n", PORT);

    // Wait for incoming requests
    while (1) {
        // Receive file name from client
        recvfrom(sockdes, fname, sizeof(fname), 0, (struct sockaddr *)&client, &client_len);
        printf("Received request for file: %s\n", fname);

        // Open the requested file
        fd = open(fname, O_RDONLY);
        if (fd < 0) {
            // If file not found, send error message to client
            char error_message[] = "File not found";
            sendto(sockdes, error_message, strlen(error_message), 0, (struct sockaddr *)&client, client_len);
            printf("File not found, sent error message.\n");
        } else {
            printf("File found, starting to send data.\n");

            // Send file content in chunks
            while ((bytesRead = read(fd, fcontent, sizeof(fcontent))) > 0) {
                printf("Sending %d bytes...\n", bytesRead);
                sendto(sockdes, fcontent, bytesRead, 0, (struct sockaddr *)&client, client_len);
            }
            printf("File sent successfully.\n");

            // Send end-of-file signal to the client
            char end_message[] = "END_OF_FILE";
            sendto(sockdes, end_message, strlen(end_message), 0, (struct sockaddr *)&client, client_len);
            printf("Sent end-of-file signal.\n");

            close(fd);
        }
    }

    close(sockdes);
    return 0;
}

