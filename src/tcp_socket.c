/*
 * tcp_socket.c
 *
 *  Created on: Feb 24, 2019
 *      Author: melchi
 */

#include "tcp_socket.h"
#include "constants.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"
#include "netinet/in.h"
#include "time.h"
#include "dirent.h"
#include "netdb.h"

#define MAX_CONN 5

int create_socket(int port_no){
	int sockfd;
	struct sockaddr_in addr;
	struct hostent * host_ent;
	char * hostAddr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons((short)port_no);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		return FAILURE;
	}

	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		return FAILURE;
	}

	return sockfd;
}

int listen_for_request(int server_socket){
	int conn;
	char hostip[32];
	struct sockaddr_in addr;
	struct hostent * host;
	struct in_addr inAddr;
	int len;

	addr.sin_family = AF_INET;

	listen(server_socket, MAX_CONN);
	len = sizeof(addr);
	if ((conn = accept(server_socket, (struct sockaddr *)&addr, &len)) < 0) {
		return FAILURE;
	}

	inet_ntop(AF_INET, &(addr.sin_addr), hostip, 32);
	inet_pton(AF_INET, hostip, &inAddr);
	host = gethostbyaddr(&inAddr, sizeof(inAddr), AF_INET);

	return conn;
}

int recv_request(int client_socket, char *recv_data){
	return recv(client_socket, recv_data, BUFFER_SIZE, 0);
}

int send_response(int client_socket, char *send_data){
	return send(client_socket, send_data, strlen(send_data), 0);
}
