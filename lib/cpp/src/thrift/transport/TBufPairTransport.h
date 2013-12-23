#ifndef  _THRIFT_TRANSPORT_TBUFPAIRTRANSPORT_H_
#define _THRIFT_TRANSPORT_TBUFPAIRTRANSPORT_H_ 1

#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TVirtualTransport.h>

namespace apache { namespace thrift { namespace transport {

class TBufPairTransport : public TVirtualTransport<TBufPairTransport> {
 public:
  TBufPairTransport();

  virtual ~TBufPairTransport();

  void open() {
  }

  bool isOpen();
  bool peek();

  void close() {
  }

  uint32_t read(uint8_t* buf, uint32_t len);

  uint32_t readEnd();

  void write(const uint8_t* buf, uint32_t len);

  virtual void flush();

  boost::shared_ptr<TMemoryBuffer> getIn();
  boost::shared_ptr<TMemoryBuffer> getOut();

 protected:
  boost::shared_ptr<TMemoryBuffer> input_;
  boost::shared_ptr<TMemoryBuffer> output_;
};

}}} // apache::thrift::transport

#endif // #ifndef _THRIFT_TRANSPORT_THTTPCLIENT_H_
