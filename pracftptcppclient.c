#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main() {
    int sockdes;
    FILE *fd;
    char s[100] = "";
    char s2[25] = "";
    char s1[2000] = "";
    struct sockaddr_in client;

    // Create socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdes == -1) {
        printf("Cannot create socket\n");
        return 1;
    }

    // Prepare client address (use the server's IP address here)
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");  // Change this to the server's IP address
    client.sin_port = htons(8888);

    // Connect to server
    if (connect(sockdes, (struct sockaddr *)&client, sizeof(client)) < 0) {
        printf("Connection error\n");
        return 1;
    }
    printf("\nEnter the file name to request from the server: ");
    scanf("%s", s);
    printf("\nEnter the new file name to save: ");
    scanf("%s", s2);

    // Send file name to server
    write(sockdes, s, strlen(s));

    // Open file to write received data
    fd = fopen(s2, "w");
    if (fd == NULL) {
        printf("Failed to open file for writing\n");
        close(sockdes);
        return 1;
    }

    // Receive and write file content
    int bytesRead;
    while ((bytesRead = read(sockdes, s1, sizeof(s1))) > 0) {
        fwrite(s1, 1, bytesRead, fd);
    }

    printf("\nFile received successfully\n");

    // Close file and socket
    fclose(fd);
    close(sockdes);

    return 0;
}

