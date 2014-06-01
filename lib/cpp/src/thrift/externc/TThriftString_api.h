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

#ifndef _THRIFT_EXTERNC_THRIFTSTRING_API_H_
#define _THRIFT_EXTERNC_THRIFTSTRING_API_H_

#include <thrift/externc/TContext_api.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _thrift_str_handle* thrift_string_handle;
typedef const struct _thrift_str_handle* thrift_string_const_handle;

thrift_string_handle	create_thrift_string(thrift_context_handle);
void			destroy_thrift_string(thrift_context_handle, thrift_string_handle);
	
unsigned int		thrift_string_size(thrift_string_const_handle);
const char*     thrift_string_cstr(thrift_string_const_handle);
void			thrift_string_to_array(thrift_string_const_handle, char**, unsigned int*);
void			thrift_string_set_array(thrift_string_handle, const char*, int);

#ifdef __cplusplus
}
#endif

#endif
