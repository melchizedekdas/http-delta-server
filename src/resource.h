/*
 * resource.h
 *
 *  Created on: Feb 23, 2019
 *      Author: melchi
 */

//returns current version id of the resource or null pointer if resource doesn't exist
char *get_current_version_id(char *resource_path);

//returns number of bytes fetched or -1 for error
int get_resource(char *resource_path, char *resource_data);

//returns number of bytes fetched or -1 for error
int get_resource_parts(char *resource_path, char *cached_version_id, char *resource_data);
