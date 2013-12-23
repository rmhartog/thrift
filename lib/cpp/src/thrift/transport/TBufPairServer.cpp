#include <thrift/thrift-config.h>

#include "thrift/TBufPairServer.h"
#include <boost/shared_ptr.hpp>

namespace apache { namespace thrift { namespace transport {

using namespace std;
using boost::shared_ptr;

TBufPairServer::TBufPairServer()
{}

TBufPairServer::~TBufPairServer() {
  close();
}

void TBufPairServer::listen() {
}

shared_ptr<TTransport> TBufPairServer::acceptImpl() {
  if (messages.empty()) {
    throw new TTransportException("No messages available.");
  }
  
  shared_ptr<TBufPairTransport> top = messages.back();
  messages.pop_back();

  return top;
}

void TBufPairServer::interrupt() {
}

void TBufPairServer::close() {
}

void TBufPairServer::addExchange(shared_ptr<TBufPairTransport> buffer) {
  messages.push_back(buffer);
}

}}} // apache::thrift::transport
