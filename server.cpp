#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//file manage header
#include <arpa/inet.h>
#include <sys/socekt.h>//socket programming lib

void Error_handle(char *err_msg){//Error function
	fputs(err_msg,stderr);
	fputc('\n',stderr);
	exit(1);
}
int main(){
	//server client socket 
	int server_socket,client_socket;
	//declare structure variable
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	char Sendmsg[] = "Hello Hoon";
	char Recmsg[1024];
	char ip[] = "127.0.0.1";//local
	int port = 10000;
	//Create Server Socket TCP/IP Protocal
	server_socket = socket(PF_INET,SOCKET_STREAM,0);
	if(server_socket == -1) Error_handle("Socket Error!");//when error occured

	memset(&server_addr,0,sizeof(server_addr));//init
	server_addr.sin_faily = AF_INET;//TCP/IP protocal
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP addr 4bytes structure
	server_addr.sin_port = htons(port);//port number

	//bind allocate server socket addr
	int Bind_ret = bind(server_socket,(struct sockaddr*) &server_addr,sizeof(server_addr));
	if(Bind_ret == -1) Error_handle("Bind Error!");
}
