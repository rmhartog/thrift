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

#ifndef _THRIFT_EXTERNC_EXTERNAL_H_
#define _THRIFT_EXTERNC_EXTERNAL_H_

#include <thrift/externc/TThriftList.h>
#include <thrift/externc/TThriftString_api.h>

#include <string>
#include <vector>
#include <stdint.h>
#include <stdbool.h>

template<typename R, typename T> R externalize(T i);

inline int32_t externalize(const int32_t& i) {
  return i;
}

inline template<typename R, typename T>
typename enable_if<is_same<R, T>, R>::type internalize(T& i) {
  return i;
}

inline thrift_string_const_handle externalize(const std::string *in) {
  return reinterpret_cast<thrift_string_const_handle>(in);
}

inline template<typename R, typename T>
std::string internalize(thrift_string_const_handle in) {
  return std::string(*reinterpret_cast<const std::string*>(in));
}

inline template<typename E> thrift_list_handle externalize(const std::vector<E>& vector) {
  return wrap_vector(vector);
}

inline template<typename R, typename T>
typename enable_if<is_vector<R>, R>::type internalize(thrift_list_handle const in) {
  return implode<typename R::value_type>(*reinterpret_cast<std::vector<void*>*>(in));
}

#endif
