/*
 * http.c
 *
 *  Created on: Feb 24, 2019
 *      Author: melchi
 */

#include "http.h"
#include "constants.h"
#include<string.h>

#define NEW_LINE "\n"
#define SPACE " "
#define HEADER_DELIM ": "
#define ENCODING_DELIM ": "
#define GET "GET"
#define HTTP_V "HTTP/1.1"
#define BAD_REQUEST "400"
#define VERSION_ID_REQ "If-None-Match"
#define ACCEPT_ENCODING "Accept-Encoding"
#define DELTA_ENCODING "delta"

int parse_request(char *request_data, struct http_request *request){
	//parse first line of request
	if(strcmp(GET,strtok(request_data, SPACE))){
		//1st token of first line is method name. only GET is supported.
		return BAD_REQUEST;
	}
	//2nd token of first line is path
	request->path=strtok(NULL, SPACE);
	if(strcmp(HTTP_V,strtok(NULL, NEW_LINE))){
		//3rd token of first line is http version number. only http/1.1 is supported.
		return BAD_REQUEST;
	}
	//parse headers
	char *header = strtok(NULL, NEW_LINE);
	char *header_key, *header_value, *save_ptr;

	request->accept_parts=false;
	while (header != NULL) {
		//code to parse header line
		if(strlen(header)==0){
			//Empty line. Implies header over
			break;
		}
		header_key=strtok_r(header, HEADER_DELIM, &save_ptr);
		header_value=strtok_r(NULL, HEADER_DELIM, &save_ptr);
		//Use header key and value
		if(!strcmp(header_key,VERSION_ID_REQ)){
			request->version_id=header_value;
		}
		else if(!strcmp(header_key,ACCEPT_ENCODING)){
			char *encoding_save_ptr;
			char *encoding=strtok_r(header_value, ENCODING_DELIM, &encoding_save_ptr);
			while (encoding != NULL) {
				if(!strcmp(encoding,DELTA_ENCODING)){
					request->accept_parts=true;
				}
				encoding=strtok_r(NULL, ENCODING_DELIM, &encoding_save_ptr);
			}
		}
		header = strtok(NULL, NEW_LINE);
	}
	return SUCCESS;
}

int generate_response(struct http_response *response, char *response_data){
	//to be implemented

	return SUCCESS;
}
