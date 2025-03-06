#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main() {
    int s, n, fd, c;
    char fn[25] = "", fc[2000] = "";
    struct sockaddr_in server, client;

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server details
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind socket
    bind(s, (struct sockaddr *)&server, sizeof(server));
    printf("Bind done\n");

    // Listen for connections
    listen(s, 3);
    printf("Waiting for incoming connections...\n");

    c = sizeof(struct sockaddr_in);
    n = accept(s, (struct sockaddr *)&client, (socklen_t *)&c);
    printf("Connection accepted\n");

    // Receive filename
    recv(n, fn, sizeof(fn), 0);
    printf("Requested file: %s\n", fn);

    // Open requested file
    fd = open(fn, O_RDONLY);

    // Send file contents
    int b;
    while ((b = read(fd, fc, sizeof(fc))) > 0) {
        write(n, fc, b);
    }

    printf("File sent successfully\n");

    // Close file and socket
    close(fd);
    close(n);
    close(s);

    return 0;
}
 