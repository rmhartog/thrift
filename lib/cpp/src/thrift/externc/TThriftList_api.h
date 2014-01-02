/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef _THRIFT_EXTERNC_THRIFTLIST_API_H_
#define _THRIFT_EXTERNC_THRIFTLIST_API_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _thrift_list_handle* thrift_list_handle;

thrift_list_handle	create_thrift_list();
void			destroy_thrift_list(thrift_list_handle);
	
void			thrift_list_add(thrift_list_handle, void*);
void*			thrift_list_get(thrift_list_handle, unsigned int);
unsigned int		thrift_list_size(thrift_list_handle);
void			thrift_list_to_array(thrift_list_handle, void***, unsigned int*);
void			thrift_list_set_array(thrift_list_handle, void**, unsigned int);

#ifdef __cplusplus
}
#endif

#endif
