#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//file manage function header
#include <arpa/inet.h>
#include <sys/socket.h>//socket programming function decalre
#include <pthread.h>
void Error_handle(const char *Error_msg){
	fputs(Error_msg,stderr);
	fputc('\n',stderr);
	exit(1);
}
const char *Socket_Err = "Socket Error!";
const char *Connect_Err = "Connect Error!";
const char *Stop = "stop";
void* Send_function(void* sck){
	int *socket = (int*)sck;
  char message[30];
	while(1){
    fgets(message,sizeof(char)*30,stdin);
		write(*socket,message,sizeof(message));
	}
}

void* Receive_function(void* sck){
  int *socket = (int*)sck;
  char message[30];
	while(1){
		int str_len = read(*socket,message,sizeof(char)*30);
    if(str_len == 0) close(*socket);
		if(str_len != -1){
				printf("Server : %s",message);
		}
	}
}

int main(){
	//Client Socket description variable declare
	int client_socket;

	//structure variable decalre
	
	struct sockaddr_in Server_addr;

	//message
	char Recmsg[30];

	//IP/Port
	char ip[] = "172.16.95.128";
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
	else printf("Connect!\n");

	pthread_t p_thread[2];

	int result;

	pthread_create(&p_thread[0],NULL,Send_function,(void*)&client_socket);
	pthread_create(&p_thread[1],NULL,Receive_function,(void*)&client_socket);

	pthread_join(p_thread[0],(void**)&result);
	pthread_join(p_thread[1],(void**)&result);
	close(client_socket);
	return 0;
}
