/*
 * http.h
 *
 *  Created on: Feb 23, 2019
 *      Author: melchi
 */

struct http_request{
	char *path;
	char *version_id;
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
