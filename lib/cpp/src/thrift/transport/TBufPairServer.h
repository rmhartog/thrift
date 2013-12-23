#ifndef _THRIFT_TRANSPORT_TBUFPAIRSERVER_H_
#define _THRIFT_TRANSPORT_TBUFPAIRSERVER_H_ 1

#include <thrift/transport/TServerTransport.h>
#include "thrift/TBufPairTransport.h"
#include <thrift/cxxfunctional.h>
#include <boost/shared_ptr.hpp>
#include <deque>

namespace apache { namespace thrift { namespace transport {

class TBufPairServer : public TServerTransport {
 public:
  TBufPairServer();

  ~TBufPairServer();

  void listen();
  void close();

  void interrupt();

  void addExchange(boost::shared_ptr<TBufPairTransport>);

 protected:
  boost::shared_ptr<TTransport> acceptImpl();

 private:
  std::deque<boost::shared_ptr<TBufPairTransport> > messages;
};

}}} // apache::thrift::transport

#endif // #ifndef _THRIFT_TRANSPORT_TBUFPAIRSERVER_H_
