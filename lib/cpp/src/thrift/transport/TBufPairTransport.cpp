#include <thrift/transport/TBufPairTransport.h>

namespace apache { namespace thrift { namespace transport {

using namespace std;

TBufPairTransport::TBufPairTransport() : input_(new TMemoryBuffer()), output_(new TMemoryBuffer()) {
}

TBufPairTransport::~TBufPairTransport() {
}

bool TBufPairTransport::isOpen() {
  return input_->isOpen() && output_->isOpen();
}

bool TBufPairTransport::peek() {
  return input_->peek();
}

uint32_t TBufPairTransport::read(uint8_t* buf, uint32_t len) {
  return input_->read(buf, len);
}

uint32_t TBufPairTransport::readEnd() {
  return input_->readEnd();
}

void TBufPairTransport::write(const uint8_t* buf, uint32_t len) {
  output_->write(buf, len);
}

void TBufPairTransport::flush() {
  output_->flush();
}

boost::shared_ptr<TMemoryBuffer> TBufPairTransport::getIn() {
  return input_;
}

boost::shared_ptr<TMemoryBuffer> TBufPairTransport::getOut() {
  return output_;
}

}}}
