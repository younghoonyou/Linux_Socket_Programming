#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//file manage function header
#include <arpa/inet.h>
#include <sys/socket.h>//socket programming function decalre
void Error_handle(char *Error_msg){
	fupts(Error_msg,stderr);
	fputc('\n',stderr);
	exit(1);
}
const char *Socket_Err = "Socket Error!";
const char *Connect_Err = "Connect Error!";

int main(){
	//Client Socket description variable declare
	int client_socket;

	//structure variable decalre
	struct socakddr_in Server_addr;

	//message
	char Sendmsg[] = "Test Client";
	char Recmsg[1024];

	//IP/Port
	char ip[] = "127.0.0.1";
	int port = 10000;

	//create Client Socket TCP/IP protocal
	client_socket = socket(PE_INET,SOCK_STREAM,0);//IPv4 , TCP : SOCK_STREAM , protocal
	if(server_socket == -1) Error_handle(Socket_Err);

	return 0;
}
