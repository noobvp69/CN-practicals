#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main() {
    int sockdes, newsock, fd, c;
    char fname[25] = "";
    char fcontent[2000] = "";
    struct sockaddr_in server, client;

    // Create socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdes == -1) {
        printf("Cannot create socket\n");
        return 1;
    }

    // Prepare server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind socket
    if (bind(sockdes, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Bind failed\n");
        return 1;
    }
    printf("Bind done\n");

    // Listen for incoming connections
    listen(sockdes, 3);
    printf("Waiting for incoming connections...\n");

    c = sizeof(struct sockaddr_in);
    newsock = accept(sockdes, (struct sockaddr *)&client, (socklen_t *)&c);
    if (newsock < 0) {
        printf("Connection failed\n");
        return 1;
    }
    printf("Connection accepted\n");

    // Receive file name
    recv(newsock, fname, sizeof(fname), 0);

    // Open the file
    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        write(newsock, "File not found", 15);
    } else {
        // Read file and send content
        int bytesRead;
        while ((bytesRead = read(fd, fcontent, sizeof(fcontent))) > 0) {
            write(newsock, fcontent, bytesRead);
        }
    }

    close(fd);
    close(newsock);
    close(sockdes);

    return 0;
}

