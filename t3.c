#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main()
{
    int sockdes,fd,b;
    struct sockaddr_in server,client;
    char fn[25]="",fc[2000]="";
    socklen_t c = sizeof(client);
    sockdes = socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(sockdes,(struct sockaddr*)&server,sizeof(server));
    printf("Bind done.\n");
    recvfrom(sockdes,fn,sizeof(fn),0,(struct sockaddr*)&client,&c);
    printf("Requested file: %s",fn);
    fd = open(fn,O_RDONLY);
    b=read(fd,fc,sizeof(fc));
    sendto(sockdes,fc,b,0,(struct sockaddr*)&client,c);
    printf("File sent successfuly.\n");
    close(fd);
    close(sockdes);
}