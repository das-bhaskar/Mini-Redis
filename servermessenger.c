

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void die (const char *msg){

	perror(msg);
	exit(EXIT_FAILURE);
}

static void do_something(int connfd){

	char rbuf[64] = {};
	ssize_t n = recv(connfd,rbuf,sizeof(rbuf)-1, 0);

	//if error
	if(n<0){

	puts("recv() error");
	return;

	}
	printf("client message: %s\n",rbuf);

	//now writing and sending that data to client

	char wbuf[90];
	printf("enter message to send :\n" );
	fgets(wbuf,sizeof(wbuf),stdin);
	send(connfd, wbuf,strlen(wbuf),MSG_CONFIRM);

}

int main(){

	// here tcp_socket is the fd 
	int tcp_socket = socket(AF_INET, SOCK_STREAM,0);

	//setting the option val =1 which changes the behaviour keeping it default with 1 
	int val = 1;
	setsockopt(tcp_socket,SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	// we then bind file descriptor(tcp_socket) with the address
	//step3
	
	struct sockaddr_in addr={};
	addr.sin_family =AF_INET;
	addr.sin_port = htons(1234); //port 1234 in big endian form
	addr.sin_addr.s_addr = htonl (0); // address 0.0.0.0 in big endian long form
	int rv = bind (tcp_socket,(const struct sockaddr *)&addr, sizeof(addr));
	
printf("%d",rv);

	if(rv) 
	{die("bind()");}

	//step 4 
	//listen -> socket is created after listen()
	rv = listen (tcp_socket,SOMAXCONN);

	if(rv) 
	{die ("listen()");}

	
	//step 5 -> we will now accept connection


		struct sockaddr_in client_addr ={};
		socklen_t addrlen = sizeof(client_addr);

		int connfd =accept(tcp_socket,(struct sockaddr *)&client_addr, &addrlen);
		if(connfd<0) // this is if error is returned 
	
die("accept()");

	while (true){
	
	do_something(connfd);

	 
//	close(connfd);

	} // step 6 is creatring the do_something function which will read and write 



return 0;



}
