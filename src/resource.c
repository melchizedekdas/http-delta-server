/*
 * resource.c
 *
 *  Created on: Feb 24, 2019
 *      Author: melchi
 */

#include<stdio.h>
#include "resource.h"
#include "constants.h"

#define META_SUFFIX "_meta"
#define META_EXTENSION ".txt"

#define RESOURCE_EXTENSION ".html"

#define DELTA_EXTENSION ".delta"
#define VERSION_ID_SIZE 10

char *get_current_version_id(char *resource_path){
	char *version_id[VERSION_ID_SIZE];
	// Open file
	FILE *fptr = fopen(resource_path, "r");
	if (fptr == NULL)
	{
		return NULL;
	}
	// Read contents from file
	if(!fgets(version_id, VERSION_ID_SIZE, fptr)){
		return NULL;
	}
	int size=strlen(version_id);
	if(!size){
		//empty file
		return NULL;
	}
	//truncate new line character at the end;
	version_id[size-1]=version_id[size-1]=='\n'?0:version_id[size-1];
	fclose(fptr);
	return version_id;
}

int get_resource(char *resource_path, char *resource_data){
	//to be implemented

	return SUCCESS;
}

int get_resource_parts(char *resource_path, char *cached_version_id, char *resource_data){
	//to be implemented

	return SUCCESS;
}
