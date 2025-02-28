#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{int sockdes,n;
struct sockaddr_in server,client;
char msg[2000],reply[2000];
socklen_t c;
sockdes=socket(AF_INET,SOCK_DGRAM,0);
if(sockdes==-1)
{printf("cannot create socket");}
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(8888);
if(bind(sockdes,(struct sockaddr * ) &server,sizeof(server) )<0 )
{printf("bind failed");
return 1;}
printf("Bind done\n");
c=sizeof(client);
n=recvfrom(sockdes,msg,2000,0,(struct sockaddr* ) &client,&c);
printf("from client : %s",msg );
printf("\n enter reply");
scanf("%s",reply);
sendto(sockdes,reply,2000,0,(struct sockaddr* ) &client,sizeof(server) );}
