#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//file manage header
#include <arpa/inet.h>
#include <sys/socket.h>//socket programming lib
#include <pthread.h>//using multi threading
const char *Socket_Err = "Socket Error!";
const char *Bind_Err = "Bind Error!";
const char *Listen_Err = "Listen Error!";
const char *Accept_Err = "Accept Error!";
struct rec_message{
	int* socket;
	char* message;
};
void Error_handle(const char *err_msg){//Error function
	fputs(err_msg,stderr);
	fputc('\n',stderr);
	exit(1);
}

void* Send_function(void* sck){//Pass function to thread as parameter
		int *client_socket = (int*)sck;
		while(1){
				char message[30];
				scanf("%[^\n]s",message);
				if(strcmp(message,"stop") == 0) break;
				write(*client_socket,message,sizeof(message));//send message
		}
}

void* Receive_function(void* sck){
		rec_message* socket_ = (rec_message*)sck;
		//char message[30];

		while(1){
			int str_len = read(*(socket_->socket),socket_->message,sizeof(socket_->message));
			if(str_len != -1){
					printf("Client : %s\n",socket_->message);
					str_len = 0;
			}
		}
}


int main(){
	//server client socket 
	int server_socket,client_socket;
	//declare structure variable
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	//char Sendmsg[] = "Hello Hoon";
	char Recmsg[30];
	//char ip[] = "127.0.0.1";//local
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
	int Listen_ret = listen(server_socket,10);//wait queue size is 10
	if(Listen_ret == -1) Error_handle(Listen_Err);
	else printf("Listen Server Socket\n");
	//Accept for structure and function
	unsigned int Client_addr_size = sizeof(client_addr);
	int Accept_ret = accept(server_socket,(struct sockaddr*) &client_addr, &Client_addr_size);
	if(Accept_ret == -1) Error_handle(Accept_Err);
	else{
		client_socket = Accept_ret;
		printf("Accept!!\n");
	rec_message Rec_data;
	Rec_data.socket = &client_socket;
	Rec_data.message = Recmsg;

	int result;
	pthread_t p_thread[2];
	pthread_create(&p_thread[0],NULL,Send_function,(void*)&client_socket);
	pthread_create(&p_thread[1],NULL,Receive_function,(void*)&Rec_data);

	pthread_join(p_thread[0],(void**)&result);
	pthread_join(p_thread[1],(void**)&result);

	}

	close(client_socket);
	close(server_socket);
	return 0;
}
