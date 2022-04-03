#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//file manage header
#include <arpa/inet.h>
#include <sys/socket.h>//socket programming lib
const char *Socket_Err = "Socket Error!";
const char *Bind_Err = "Bind Error!";
const char *Listen_Err = "Listen Error!";
const char *Accept_Err = "Accept Error!";
void Error_handle(const char *err_msg){//Error function
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
	server_socket = socket(PF_INET,SOCK_STREAM,0);
	if(server_socket == -1) Error_handle(Socket_Err);//when error occured
	else printf("Create Server Socket\n");
	memset(&server_addr,0,sizeof(server_addr));//init
	server_addr.sin_family = AF_INET;//TCP/IP protocal
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP addr 4bytes structure
	server_addr.sin_port = htons(port);//port number

	//bind allocate server socket addr
	int Bind_ret = bind(server_socket,(struct sockaddr*) &server_addr,sizeof(server_addr));
	if(Bind_ret == -1) Error_handle(Bind_Err);
	else printf("Bind Server Socket\n");
	//for listen wait clinet request
	int Listen_ret = listen(server_socket,10);
	if(Listen_ret == -1) Error_handle(Listen_Err);
	else printf("Listen Server Socket\n");
	//Accept for structure and function
	unsigned int Client_addr_size = sizeof(client_addr);
	int Accept_ret = accept(server_socket,(struct sockaddr*) &client_addr, &Client_addr_size);
	if(Accept_ret == -1) Error_handle(Accept_Err);
	else{
		printf("Accept!!\n");
	//	while(1){
	//		int Read_strlen = read(client_socket,Recmsg,sizeof(Recmsg) - 1);
	//		printf("%d\n",Read_strlen);
	//		if(Read_strlen > 0) printf("%s\n",Recmsg);
	//	}
	}
	//else printf("Accept!!\n");
	//send msg , contain rec msg string data
	write(client_socket,Sendmsg,sizeof(Sendmsg));
	int Read_strlen = read(client_socket,Recmsg,sizeof(Recmsg) - 1);//'\0'
	if(Read_strlen != -1) printf("client : %s\n",Recmsg);
	//printf("%s\n",Recmsg);
	printf("Server Read %d\n",Read_strlen);
	//write(client_socket,Sendmsg,sizeof(Sendmsg));
	//Close socket file
	close(client_socket);
	close(server_socket);
	return 0;
}
