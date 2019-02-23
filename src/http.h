/*
 * http.h
 *
 *  Created on: Feb 23, 2019
 *      Author: melchi
 */

#define true 1
#define false 0
#define SUCCESS 0
#define FAILURE -1
#define BUFFER_SIZE 1024

struct http_request{
	char *path;
	int version_id;
	short accept_parts;
};

struct http_response{
	int version_id, status_code;
	short same_version, parts;
	char *body;
};

//returns success or error code
int parse_request(char *request_data, struct http_request *request);

//returns success or error code
int generate_response(struct http_response *response, char *response_data);
