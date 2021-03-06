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

#include <thrift/externc/TResult.h>
#include <thrift/externc/TResult_api.h>

extern "C" bool thrift_result_is_success(thrift_result_const_handle result) {
    return result == THRIFT_SUCCESS;
}

bool thrift_result_has_exception(thrift_result_const_handle result) {
    return !thrift_result_is_success(result);
}

TException thrift_result_get_exception(thrift_result_const_handle result) {
    return *reinterpret_cast<const TException*>(result);
}
