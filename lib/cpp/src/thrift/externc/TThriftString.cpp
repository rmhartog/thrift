#include "TThriftString_api.h"

#include <cstdlib>
#include <cstring>
#include <string>

extern "C" thrift_string_handle create_thrift_string() {
    return reinterpret_cast<thrift_string_handle>(new std::string());
}

extern "C" void destroy_thrift_string(thrift_string_handle handle) {
    delete reinterpret_cast<std::string*>(handle);
}
	
extern "C" unsigned int thrift_string_size(thrift_string_const_handle handle) {
    return reinterpret_cast<const std::string*>(handle)->size();
}

extern "C" void thrift_string_to_array(thrift_string_const_handle handle, char **outbuffer, unsigned int *outsize) {
    const std::string* str = reinterpret_cast<const std::string*>(handle);
    
    unsigned int size = str->size();
    *outbuffer = (char*) malloc(size * sizeof(char));
    *outsize = size;

    memcpy(*outbuffer, str->c_str(), size);
}

extern "C" void thrift_string_set_array(thrift_string_handle handle, const char *buffer, int size) {
    if (size < 0) {
        size = strlen(buffer);
    }
    *reinterpret_cast<std::string*>(handle) = std::string(buffer, size);
}
