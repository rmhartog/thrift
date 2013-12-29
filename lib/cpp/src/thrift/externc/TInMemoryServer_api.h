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

#ifndef _THRIFT_EXTERNC_INMEMSERVER_API_H_
#define _THRIFT_EXTERNC_INMEMSERVER_API_H_

#include <thrift/externc/TProcessor_api.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _thrift_server_handle*		thrift_server_handle;
typedef const struct _thrift_server_handle*	thrift_server_const_handle;

typedef struct _thrift_message_handle*		thrift_message_handle;

int create_thrift_server(thrift_server_handle *);
int run_thrift_server(thrift_server_handle);
int destroy_thrift_server(thrift_server_handle);

int register_thrift_server_processor(thrift_server_handle, const char *, thrift_processor_handle);

int write_thrift_server_message(thrift_message_handle *, thrift_server_handle, const unsigned char *, unsigned int);
int read_thrift_server_message(thrift_message_handle, unsigned char *, unsigned int);
int close_thrift_server_message(thrift_message_handle);

#ifdef __cplusplus
}
#endif

#endif
