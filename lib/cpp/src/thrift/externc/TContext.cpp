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

#include <thrift/externc/TContext.h>
#include <thrift/externc/TContext_api.h>

TContext::TContext() {}
TContext::~TContext() {
    std::vector<TDestroyable*>::iterator destroy;
    for (destroy = destroyables.begin(); destroy != destroyables.end(); ++destroy) {
        delete *destroy;
    }
}

void TContext::newObject(TDestroyable *obj) {
    destroyables.push_back(obj);
}

extern "C" thrift_context_handle create_thrift_context() {
    return reinterpret_cast<thrift_context_handle>(new TContext());
}

extern "C" void destroy_thrift_context(thrift_context_const_handle h) {
    delete reinterpret_cast<TContext const *>(h);
}
