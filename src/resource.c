/*
 * resource.c
 *
 *  Created on: Feb 24, 2019
 *      Author: melchi
 */

#include<stdio.h>
#include<stdlib.h>
#include "resource.h"
#include "constants.h"
#include <string.h>

#define RESOURCES_PREFIX "../web-inf"

#define META_SUFFIX "_meta"
#define META_EXTENSION ".txt"

#define RESOURCE_EXTENSION ".html"

#define VERSION_ID_SEPARATOR "_"
#define DELTA_EXTENSION ".delta"

#define VERSION_ID_SIZE 10

char *get_current_version_id(char *resource_path){
	char *version_id=(char *)malloc(sizeof(char)*VERSION_ID_SIZE);
	// Open file
	char *file_path=(char *)malloc(sizeof(char)*(strlen(RESOURCES_PREFIX)+strlen(resource_path)+strlen(META_SUFFIX)+strlen(META_EXTENSION)+1));
	strcpy(file_path,RESOURCES_PREFIX);
	strcat(file_path,resource_path);
	strcat(file_path,META_SUFFIX);
	strcat(file_path,META_EXTENSION);
	FILE *fptr = fopen(file_path, "r");
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
	char resource_content[BUFFER_SIZE];
	// Open file
	char *file_path=(char *)malloc(sizeof(char)*(strlen(RESOURCES_PREFIX)+strlen(resource_path)+strlen(RESOURCE_EXTENSION)+1));
	strcpy(file_path,RESOURCES_PREFIX);
	strcat(file_path,resource_path);
	strcat(file_path,RESOURCE_EXTENSION);
	FILE *fptr = fopen(file_path, "r");
	if (fptr == NULL)
	{
		return FAILURE;
	}
	int chars_read=0;
	// Read contents from file
	while(fgets(resource_content+chars_read, BUFFER_SIZE-chars_read, fptr)){
		chars_read+=strlen(resource_content+chars_read);
	}
	fclose(fptr);
	resource_data=resource_content;
	return chars_read;
}

int get_resource_parts(char *resource_path, char *cached_version_id, char *resource_data){
	char resource_content[BUFFER_SIZE];
	// Open file
	char *file_path=(char *)malloc(sizeof(char)*(strlen(RESOURCES_PREFIX)+strlen(resource_path)+strlen(RESOURCE_EXTENSION)+1));
	strcpy(file_path,RESOURCES_PREFIX);
	strcat(file_path,resource_path);
	strcat(file_path,VERSION_ID_SEPARATOR);
	strcat(file_path,cached_version_id);
	strcat(file_path,DELTA_EXTENSION);
	FILE *fptr = fopen(file_path, "r");
	if (fptr == NULL)
	{
		return FAILURE;
	}
	int chars_read=0;
	// Read contents from file
	while(fgets(resource_content+chars_read, BUFFER_SIZE-chars_read, fptr)){
		chars_read+=strlen(resource_content+chars_read);
	}
	fclose(fptr);
	resource_data=resource_content;
	return chars_read;
}
