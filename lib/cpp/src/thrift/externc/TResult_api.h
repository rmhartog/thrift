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

#ifndef _THRIFT_EXTERNC_RESULT_API_H_
#define _THRIFT_EXTERNC_RESULT_API_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _thrift_result_handle* thrift_result_handle;
typedef const struct _thrift_result_handle* thrift_result_const_handle;

#define THRIFT_SUCCESS ((thrift_result_handle) 0)

bool thrift_result_is_success(thrift_result_const_handle);

#ifdef __cplusplus
}
#endif

#endif
