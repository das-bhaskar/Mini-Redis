#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

void die(const char *msg){

	perror(msg);
exit(EXIT_FAILURE);
}

int main(){
	int clientsocket = socket(AF_INET,SOCK_STREAM,0);
	if (clientsocket<0)
		die("socket()");

	//preparing the socket 
	struct sockaddr_in addr = {};
	addr.sin_family =AF_INET;
	addr.sin_port=htons(1234);
	char ip[]="192.168.0.112";
	addr.sin_addr.s_addr = inet_addr(ip);
	int rv = connect(clientsocket,(const struct sockaddr *)&addr,sizeof(addr));

	char msg[] = "hi from mac";
	send(clientsocket, msg, strlen(msg),MSG_DONTROUTE);

	//read buffer
	char rbuf[64]={};
	ssize_t n = recv(clientsocket,rbuf, sizeof(rbuf)-1,0);
	if(n<0)
		die("recv()");

	printf("message from hp server: %s\n",rbuf);
	close(clientsocket);
return 0;
} 
