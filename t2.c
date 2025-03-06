#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main() {
    int sockdes, b;
    char f[100], nf[25], bf[2000];
    struct sockaddr_in client;
    FILE *fd; 
    
    sockdes = socket(AF_INET, SOCK_STREAM, 0);
    
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");  
    client.sin_port = htons(8888);


    connect(sockdes, (struct sockaddr*)&client, sizeof(client));
    printf("\nEnter file name to request: ");
    scanf("%s", f);
    printf("Enter new file name to save: ");
    scanf("%s", nf);

    write(sockdes, f, strlen(f));
    fd = fopen(nf, "w");

    while ((b = read(sockdes, bf, sizeof(bf))) > 0) {
        fwrite(bf, 1, b, fd);
    }

    printf("\nFile received successfully\n");

    fclose(fd);
    close(sockdes);

    return 0;
}
