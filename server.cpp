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
	struct sockaddr_int client_addr;

	char Sendmsg[] = "Hello Hoon";
	char Recmsg[1024];
	char ip[] = "127.0.0.1";//local
	int port = 10000;
	//Create Server Socket TCP/IP Protocal
	server_socket = socket(PF_INET,SOCKET_STREAM,0);
	if(server_socket == -1) Error_handle("Socket Error!");//when error occured

}
