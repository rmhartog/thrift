#include "TThriftList.h"
#include "TThriftList_api.h"

extern "C" thrift_list_handle create_thrift_list() {
    return reinterpret_cast<thrift_list_handle>(new std::vector<void*>());
}

extern "C" void destroy_thrift_list(thrift_list_handle handle) {
    delete reinterpret_cast<std::vector<void*>*>(handle);
}
	
extern "C" unsigned int thrift_list_size(thrift_list_handle handle) {
    return reinterpret_cast<std::vector<void*>*>(handle)->size();
}

extern "C" void thrift_list_to_array(thrift_list_handle handle, void ***outbuffer, unsigned int *outsize) {
    std::vector<void*>* vector = reinterpret_cast<std::vector<void*>*>(handle);
    std::vector<void*>::iterator it;
    
    unsigned int size = vector->size();
    *outbuffer = (void**) malloc(size * sizeof(void*));
    *outsize = size;

    unsigned int index = 0;
    for (it = vector->begin(); it != vector->end(); it++, index++) {
        (*outbuffer)[index] = *it;
    }
}

extern "C" void thrift_list_set_array(thrift_list_handle handle, void **buffer, unsigned int size) {
    std::vector<void*>* vector = reinterpret_cast<std::vector<void*>*>(handle);

    vector->clear();
    for (unsigned int index = 0; index < size; index++) {
        vector->push_back(buffer[index]);
    }
}
