#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{int sockdes;
struct sockaddr_in client;
char msg[2000],reply[2000];
sockdes=socket(AF_INET,SOCK_STREAM,0);
if(sockdes==-1)
{printf("\n cannot create socket");}
client.sin_family=AF_INET;
client.sin_addr.s_addr=INADDR_ANY;
client.sin_port=htons(8888);
if(connect(sockdes,(struct sockaddr * ) &client,sizeof(client) )<0 )
{printf("\n connection error");
return 1;}
while(1)
{printf("\n To server: ");
scanf("%s",msg);
send(sockdes,msg,2000,0);
recv(sockdes,reply,2000,0);
printf("\n From server: ");
puts(reply);}
return 0;}

