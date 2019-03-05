/*
 * tcp_socket.h
 *
 *  Created on: Feb 23, 2019
 *      Author: melchi
 */

//returns server socket_fd
int create_socket(int port_no);

//returns client socket_fd
int listen_for_request(int server_socket);

//returns the number of bytes transmitted, or -1 on failure
int recv_request(int client_socket, char *recv_data, int buffer_size);

//returns the number of bytes received, or -1 on failure.
int send_response(int client_socket, char *send_data);
