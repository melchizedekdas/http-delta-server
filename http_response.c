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

int process_request(struct http_request *request, struct http_response *response){
	char * current_version_id=get_current_version_id(request->path);
	if(!current_version_id){
		//Resource not found
		response->status_code=RESOURCE_NOT_FOUND;
		return SUCCESS;
	}
	if(!strcmp(current_version_id,request->version_id)){
		//same version as client cache
		response->status_code=SAME_VERSION;
		return SUCCESS;
	}

	char *resource_data[BUFFER_SIZE];
	if((request->accept_parts==true)&&((response->content_length=get_resource_parts(request->path, request->version_id, resource_data))>=0)){
		//fetched parts resource
		response->version_id=current_version_id;
		response->body=resource_data;
		response->status_code=PARTS_FOUND;
		return SUCCESS;
	}
	//whole resource
	if((response->content_length=get_resource(request->path, resource_data))>=0){
		return FAILURE;
	}
	response->version_id=current_version_id;
	response->body=resource_data;
	response->status_code=RESOURCE_FOUND;
	return SUCCESS;
}
