/*
 * http_response.c
 *
 *  Created on: Feb 23, 2019
 *      Author: melchi
 */

#include "http.h"
#include "http_response.h"
#include "resource.h"
#include "constants.h"

#define RESOURCE_FOUND 200
#define SAME_VERSION 201
#define PARTS_FOUND 202
#define RESOURCE_NOT_FOUND 404

int process_request(struct http_request *request, struct http_response *response){
	int current_version_id=get_current_version_id(request->path);
	if(current_version_id==FAILURE){
		//Resource not found
		response->status_code=RESOURCE_NOT_FOUND;
		return SUCCESS;
	}
	if(current_version_id==request->version_id){
		//same version as client cache
		response->same_version=true;
		response->status_code=SAME_VERSION;
		return SUCCESS;
	}

	char *resource_data[BUFFER_SIZE];
	if((request->accept_parts==true)&&(!get_resource_parts(request->path, request->version_id, resource_data))){
		//fetched parts resource
		response->same_version=false;
		response->version_id=current_version_id;
		response->body=resource_data;
		response->status_code=PARTS_FOUND;
		response->parts=true;
		return SUCCESS;
	}
	//whole resource
	if(get_resource(request->path, resource_data)){
		return FAILURE;
	}
	response->same_version=false;
	response->version_id=current_version_id;
	response->body=resource_data;
	response->status_code=RESOURCE_FOUND;
	response->parts=true;
	return SUCCESS;
}
