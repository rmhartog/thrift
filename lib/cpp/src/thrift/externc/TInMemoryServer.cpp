#include <thrift/externc/TInMemoryServer.h>
#include <thrift/externc/TInMemoryServer_api.h>

using namespace ::apache::thrift::externc;

void TInMemoryServer::registerProcessor(const char * service, shared_ptr<TProcessor> processor) {
  muxer_->registerProcessor(service, processor);
}

extern "C" int create_thrift_server(thrift_server_handle * handle) {
  if (handle == 0) {
    return -1;
  } else {
    *handle = reinterpret_cast<thrift_server_handle>(new TInMemoryServer());
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
