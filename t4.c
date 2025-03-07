#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
int main(){
    int sockdes,b;
    char f[100]="",nf[25]="",bf[2000]="";
    struct sockaddr_in server;
    FILE *fd;
    sockdes = socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port=htons(8888);
    printf("Enter the file name: ");
    scanf("%s",f);
    printf("Enter the new file name: ");
    scanf("%s",nf);
    sendto(sockdes,f,strlen(f),0,(struct sockaddr*)&server,sizeof(server));
    fd = fopen(nf,"wb");
    b=recvfrom(sockdes,bf,sizeof(bf),0,NULL,NULL);
    fwrite(bf,1,b,fd);
    fclose(fd);
    close(sockdes);
}