#include <stdio.h>
#include "tcp_socket.h"
#include "http.h"
#include "http_response.h"
#include "constants.h"

#define PORT 8080

int main(){
	int server_socket=create_socket(PORT), client_socket, bytes_received;
	char request_data[BUFFER_SIZE], response_data[BUFFER_SIZE];
	struct http_request request;
	struct http_response response;
	while(true){
		client_socket=listen_for_request(server_socket);
		bytes_received=recv_request(client_socket, request_data);
		if(bytes_received==FAILURE){
			printf("Error while receiving data");
			return SUCCESS;
		}
		if(parse_request(request_data, &request)){
			printf("Error while parsing request");
			return SUCCESS;
		}
		if(process_request(&request, &response)){
			printf("Error while processing request");
			return SUCCESS;
		}
		if(generate_response(&response, response_data)){
			printf("Error while generating response");
			return SUCCESS;
		}
		if(send_response(client_socket, response_data)){
			printf("Error while sending data");
			return SUCCESS;
		}
	}
	return SUCCESS;
}
