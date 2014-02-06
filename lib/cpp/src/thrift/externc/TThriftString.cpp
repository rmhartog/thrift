#include "TThriftString.h"
#include "TThriftString_api.h"

#include <cstdlib>
#include <cstring>
#include <string>

TThriftString::TThriftString() : str(new std::string) {}
TThriftString::TThriftString(std::string *s) : str(s) {}
TThriftString::~TThriftString() {
    delete str;
}

std::string* TThriftString::getString() {
    return str;
}

const std::string* TThriftString::getString() const {
    return str;
}

std::string* thrift_string_get_string(thrift_string_handle handle) {
    return reinterpret_cast<TThriftString*>(handle)->getString();
}

const std::string* thrift_string_get_string_const(thrift_string_const_handle handle) {
    return reinterpret_cast<const TThriftString*>(handle)->getString();
}

extern "C" thrift_string_handle create_thrift_string(thrift_context_handle ctx) {
    return reinterpret_cast<thrift_string_handle>(new TThriftString);
}

extern "C" void destroy_thrift_string(thrift_context_handle ctx, thrift_string_handle handle) {
    delete reinterpret_cast<TThriftString*>(handle);
}
	
extern "C" unsigned int thrift_string_size(thrift_string_const_handle handle) {
    return thrift_string_get_string_const(handle)->size();
}

extern "C" void thrift_string_to_array(thrift_string_const_handle handle, char **outbuffer, unsigned int *outsize) {
    const std::string* str = thrift_string_get_string_const(handle);
    
    unsigned int size = str->size();
    *outbuffer = (char*) malloc(size * sizeof(char));
    *outsize = size;

    memcpy(*outbuffer, str->c_str(), size);
}

extern "C" void thrift_string_set_array(thrift_string_handle handle, const char *buffer, int size) {
    if (size < 0) {
        size = strlen(buffer);
    }
    *thrift_string_get_string(handle) = std::string(buffer, size);
}
