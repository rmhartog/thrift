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

#ifndef _THRIFT_EXTERNC_INMEMSERVER_H_
#define _THRIFT_EXTERNC_INMEMSERVER_H_

#include <thrift/processor/TMultiplexedProcessor.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufPairServer.h>
#include <thrift/protocol/TCompactProtocol.h>

using namespace ::apache::thrift::server;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::protocol;

using ::boost::static_pointer_cast;

namespace apache { namespace thrift { namespace externc {

class TMuxerOwner {
 public:
  TMuxerOwner() : muxer_(new TMultiplexedProcessor()) {}

  ~TMuxerOwner() {}

 protected:
  boost::shared_ptr<TMultiplexedProcessor> muxer_;
};

class TInMemoryServer : public TMuxerOwner, public TSimpleServer {
 public:
  TInMemoryServer() : TMuxerOwner(), TSimpleServer(
                        boost::shared_ptr<TProcessor>(muxer_),
                        boost::shared_ptr<TBufPairServer>(new TBufPairServer()),
                        boost::shared_ptr<TTransportFactory>(new TBufferedTransportFactory()),
                        boost::shared_ptr<TProtocolFactory>(new TCompactProtocolFactory())) {
    buffer_ = static_pointer_cast<TBufPairServer>(getServerTransport());
  }

  ~TInMemoryServer() {}

  void registerProcessor(const char *, shared_ptr<TProcessor>);

 protected:
  boost::shared_ptr<TBufPairServer> buffer_;
};

}}}

#endif
