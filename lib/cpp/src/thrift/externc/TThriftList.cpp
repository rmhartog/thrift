#include "TThriftList.h"
#include "TThriftList_api.h"

#include <stdexcept>

TThriftList::TThriftList() : vector(new std::vector<void*>) {}
TThriftList::~TThriftList() {
    delete vector;
}

std::vector<void*>* TThriftList::getVector() {
    return vector;
}

std::vector<void*>* get_thrift_list_vector(thrift_list_handle handle) {
    return reinterpret_cast<TThriftList*>(handle)->getVector();
}

extern "C" thrift_list_handle create_thrift_list(thrift_context_handle ctx) {
    TThriftList *list = new TThriftList;
    reinterpret_cast<TContext*>(ctx)->newObject(list);
    return reinterpret_cast<thrift_list_handle>(list);
}

extern "C" void destroy_thrift_list(thrift_context_handle ctx, thrift_list_handle handle) {
    delete reinterpret_cast<TThriftList*>(handle);
}

extern "C" void thrift_list_add(thrift_list_handle handle, void *element) {
    get_thrift_list_vector(handle)->push_back(element);
}

extern "C" void* thrift_list_get(thrift_list_handle handle, unsigned int index) {
    std::vector<void*>* vector = get_thrift_list_vector(handle);
    
    try {
        return vector->at(index);
    }
    catch (std::out_of_range& oor) {
        return (void*) 0;
    }
}

extern "C" unsigned int thrift_list_size(thrift_list_handle handle) {
    return get_thrift_list_vector(handle)->size();
}

extern "C" void thrift_list_to_array(thrift_list_handle handle, void ***outbuffer, unsigned int *outsize) {
    std::vector<void*>* vector = get_thrift_list_vector(handle);
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
    std::vector<void*>* vector = get_thrift_list_vector(handle);

    vector->clear();
    for (unsigned int index = 0; index < size; index++) {
        vector->push_back(buffer[index]);
    }
}
