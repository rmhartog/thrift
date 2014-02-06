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
#include <thrift/externc/TThriftString.h>

#include <string>
#include <vector>
#include <stdint.h>
#include <stdbool.h>

template<typename R, typename T> R externalize(T i);

inline int32_t externalize(thrift_context_handle, const int32_t& i) {
  return i;
}

template<typename R, typename T> inline 
typename enable_if<is_same<R, T>, R>::type internalize(T& i) {
  return i;
}

inline thrift_string_const_handle externalize(thrift_context_handle ctx, std::string *in) {
  TThriftString *str = new TThriftString(in);
  reinterpret_cast<TContext*>(ctx)->newObject(str);
  return reinterpret_cast<thrift_string_const_handle>(str);
}

inline thrift_string_const_handle externalize(thrift_context_handle ctx, const std::string *in) {
  thrift_string_handle str = create_thrift_string(ctx);
  thrift_string_set_array(str, in->c_str(), in->size());
  return str;
}

template<typename R, typename T> inline
std::string internalize(thrift_string_const_handle in) {
  return std::string(*reinterpret_cast<const TThriftString*>(in)->getString());
}

template<typename E> inline thrift_list_handle externalize(thrift_context_handle ctx, const std::vector<E>& vector) {
  return explode(ctx, vector);
}

template<typename E> inline thrift_list_handle externalize(thrift_context_handle ctx, std::vector<void*>& vector) {
  TThriftList *list = new TThriftList(vector);
  reinterpret_cast<TContext*>(ctx)->newObject(list);
  return reinterpret_cast<thrift_list_handle>(list);
}

template<typename R, typename T> inline
typename enable_if<is_vector<R>, R>::type internalize(thrift_list_handle const in) {
  return implode<typename R::value_type>(*reinterpret_cast<TThriftList*>(in)->getVector());
}

#endif
