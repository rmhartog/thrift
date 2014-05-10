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

#ifndef _THRIFT_EXTERNC_THRIFTLIST_H_
#define _THRIFT_EXTERNC_THRIFTLIST_H_

#include <thrift/externc/TContext.h>
#include <thrift/externc/TThriftString.h>
#include <thrift/externc/TThriftList_api.h>

#include <vector>
#include <boost/utility.hpp>
#include <boost/type_traits.hpp> 

using namespace boost;
using namespace boost::type_traits;

class TThriftList : public TDestroyable {
private:
    bool ext;
    std::vector<void*>* vector;
public:
    TThriftList();
    TThriftList(std::vector<void*>&);
    virtual ~TThriftList();

    std::vector<void*>* getVector();
};

template <typename T> struct is_vector : false_type {};
template <typename T> struct is_vector<std::vector<T> > : true_type {};

template<typename T>
thrift_list_handle explode(thrift_context_handle ctx, const std::vector<T>& v) {
    typename std::vector<T>::const_iterator it;
    thrift_list_handle out = create_thrift_list(ctx);

    for (it = v.begin(); it != v.end(); it++) {
        T* val = new T;
        *val = *it;
        thrift_list_add(out, val);
    }

    return out;
}

template<typename T>
typename disable_if< ice_or<
             is_vector<T>::value,
             is_same<T, std::string>::value
         >, std::vector<T> >::type implode(std::vector<void*>& v) {
    std::vector<void*>::const_iterator it;
    typename std::vector<T> out;

    for (it = v.begin(); it != v.end(); it++) {
        out.push_back(*reinterpret_cast<T*>(*it));
    }

    return out;
}

template<typename T>
std::vector<void*>* explode(thrift_context_handle ctx, const std::vector<std::vector<T> >& v) {
    typename std::vector<std::vector<T> >::const_iterator it;
    thrift_list_handle out = create_thrift_list(ctx);

    for (it = v.begin(); it != v.end(); it++) {
        thrift_list_add(out, explode(ctx, *it));
    }

    return out;
}

template<typename T>
typename enable_if<is_vector<T>, std::vector<T> >::type implode(std::vector<void*>& v) {
    std::vector<void*>::const_iterator it;
    typename std::vector<T> out;

    for (it = v.begin(); it != v.end(); it++) {
        out.push_back(implode<typename T::value_type>(*reinterpret_cast<TThriftList*>(*it)->getVector()));
    }

    return out;
}

template<typename T>
typename enable_if<is_same<T, std::string>, std::vector<std::string> >::type implode(std::vector<void*>& v) {
    std::vector<void*>::const_iterator it;
    typename std::vector<std::string> out;

    for (it = v.begin(); it != v.end(); it++) {
        out.push_back(*reinterpret_cast<TThriftString*>(*it)->getString());
    }

    return out;
}

#endif
