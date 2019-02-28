/*
 * server.c
 *
 *  Created on: Feb 23, 2019
 *      Author: melchi
 */

#include <stdio.h>
#include "tcp_socket.h"
#include "http.h"
#include "http_response.h"
#include "constants.h"

#define PORT 8080

int main(){
	int server_socket, client_socket, bytes_received;
	char request_data[BUFFER_SIZE], response_data[BUFFER_SIZE];
	struct http_request request;
	struct http_response response;

	server_socket=create_socket(PORT);
	while(true){
		//Infinite loop
		client_socket=listen_for_request(server_socket);
		bytes_received=recv_request(client_socket, request_data, BUFFER_SIZE);
		if(bytes_received==FAILURE){
			printf("Error while receiving data");
			return FAILURE;
		}
		if(parse_request(request_data, &request)){
			printf("Error while parsing request");
			return FAILURE;
		}
		if(process_request(&request, &response)){
			printf("Error while processing request");
			return FAILURE;
		}
		if(generate_response(&response, response_data)){
			printf("Error while generating response");
			return FAILURE;
		}
		if(send_response(client_socket, response_data)){
			printf("Error while sending data");
			return FAILURE;
		}
	}
	return SUCCESS;
}
