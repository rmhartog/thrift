#include <thrift/externc/TInMemoryServer.h>
#include <thrift/externc/TInMemoryServer_api.h>

using namespace ::apache::thrift::externc;

void TInMemoryServer::registerProcessor(const char * service, shared_ptr<TProcessor> processor) {
  muxer_->registerProcessor(service, processor);
}

void TInMemoryServer::addMessage(shared_ptr<TBufPairTransport> transport) {
  buffer_->addExchange(transport);
}

extern "C" int create_thrift_server(thrift_server_handle * handle) {
  if (handle == 0) {
    return -1;
  } else {
    *handle = reinterpret_cast<thrift_server_handle>(new TInMemoryServer());
    return 0;
  }
}

extern "C" int run_thrift_server(thrift_server_handle handle) {
  if (handle == 0) {
    return -1;
  } else {
    try {
      reinterpret_cast<TInMemoryServer*>(handle)->serve();
    } catch(const std::exception* x) {
      return -2;
    } catch(const std::exception& x) {
      return -2;
    }
    return 0;
  }
}

extern "C" int destroy_thrift_server(thrift_server_handle handle) {
  if (handle == 0) {
    return -1;
  } else {
    delete reinterpret_cast<TInMemoryServer*>(handle);
    return 0;
  }
}

extern "C" int register_thrift_server_processor(thrift_server_handle handle, const char *service, thrift_processor_handle processor) {
  if (handle == 0 || service == 0 || processor == 0) {
    return -1;
  } else {
    TInMemoryServer *server = reinterpret_cast<TInMemoryServer*>(handle);
    TProcessor *proc = reinterpret_cast<TProcessor*>(processor);
    server->registerProcessor(service, shared_ptr<TProcessor>(proc));
    return 0;
  }
}

extern "C" int write_thrift_server_message(thrift_message_handle *message, thrift_server_handle handle, const unsigned char *buffer, unsigned int size) {
  if (message == 0 || handle == 0 || buffer == 0 || size == 0) {
    return -1;
  } else {
    TInMemoryServer *server = reinterpret_cast<TInMemoryServer*>(handle);

    TMemoryMessage *msg(new TMemoryMessage());
    shared_ptr<TBufPairTransport> tp = msg->getPair();
    
    tp->getIn()->write(static_cast<const uint8_t*>(buffer), size);

    server->addMessage(msg->getPair());    

    *message = reinterpret_cast<thrift_message_handle>(msg);

    return 0;
  }
}

extern "C" int read_thrift_server_message(thrift_message_handle message, unsigned char *buffer, unsigned int size) {
  if (message == 0 || buffer == 0 || size == 0) {
    return -1;
  } else {
    TMemoryMessage* msg = reinterpret_cast<TMemoryMessage*>(message);
    shared_ptr<TBufPairTransport> tp = msg->getPair();

    return tp->getOut()->read(static_cast<uint8_t*>(buffer), size);
  }
}

extern "C" int close_thrift_server_message(thrift_message_handle message) {
  if (message == 0) {
    return -1;
  } else {
    TMemoryMessage* msg = reinterpret_cast<TMemoryMessage*>(message);
    shared_ptr<TBufPairTransport> tp = msg->getPair();

    tp->getIn()->close();
    tp->getOut()->close();

    delete msg;
    return 0;
  }
}
