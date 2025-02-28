#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{int sockdes;
struct sockaddr_in server,client;
char msg[2000],reply[2000];
socklen_t c;
sockdes=socket(AF_INET,SOCK_DGRAM,0);
if(sockdes==-1)
{printf("cannot create socket");}
client.sin_family=AF_INET;
client.sin_addr.s_addr=INADDR_ANY;
client.sin_port=htons(8888);
c=sizeof(client);
printf("Enter a message: " );
scanf("%s",msg);
sendto(sockdes,msg,2000,0,(struct sockaddr* ) &client,sizeof(server) );
recvfrom(sockdes,reply,2000,0,(struct sockaddr* ) &server,&c);
printf("\nfrom server : %s \n",reply );}
