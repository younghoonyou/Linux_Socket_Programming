#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//file manage function header
#include <arpa/inet.h>
#include <sys/socket.h>//socket programming function decalre
void Error_handle(const char *Error_msg){
	fputs(Error_msg,stderr);
	fputc('\n',stderr);
	exit(1);
}
const char *Socket_Err = "Socket Error!";
const char *Connect_Err = "Connect Error!";
const char *Stop = "stop";
int main(){
	//Client Socket description variable declare
	int client_socket;

	//structure variable decalre
	struct sockaddr_in Server_addr;

	//message
	char Sendmsg[] = "Hello Server";
	char Recmsg[1024];

	//IP/Port
	char ip[] = "127.0.0.1";
	int port = 10000;

	//create Client Socket TCP/IP protocal
	client_socket = socket(PF_INET,SOCK_STREAM,0);//IPv4 , TCP : SOCK_STREAM , protocal
	if(client_socket == -1) Error_handle(Socket_Err);
	else printf("Create Client Socket\n");
	//Init to bind
	memset(&Server_addr,0,sizeof(Server_addr));
	Server_addr.sin_family = AF_INET;//Address Family IPv4 Internet Protocal
	Server_addr.sin_addr.s_addr = inet_addr(ip);//IP addr
	Server_addr.sin_port = htons(port);//Host to network short - short 2bytes integer

	//connet to request server socket
	int Connect = connect(client_socket,(struct sockaddr*) &Server_addr,sizeof(Server_addr));
	//socekt description , casting to sockaddr structure -> to request Server addr info should be same as server
	
	if(Connect == -1) Error_handle(Connect_Err);
	else{ printf("Connect!\n");
	//	while(1){
		//	printf("1");
	//		scanf("%s",Sendmsg);
	//		if(strcmp(Sendmsg,Stop) == 0) break;
	//		write(client_socket,Sendmsg,sizeof(Sendmsg));
	//		int Read_strlen = read(client_socket,Recmsg,sizeof(Recmsg) - 1);
	//		printf("%d\n",Read_strlen);
	//	}
	//	printf("2");
	}
//	printf("3");
	//send msg receive msg for string data
	//write(client_socket,Sendmsg,sizeof(Sendmsg));
	int Read_strlen = read(client_socket,Recmsg,sizeof(Recmsg) - 1);//'\0'
	if(Read_strlen != -1) printf("server : %s\n",Recmsg);
	write(client_socket,Sendmsg,sizeof(Sendmsg));
	//printf("Read Socket %d\n",Read_strlen);
	close(client_socket);
	return 0;
}
