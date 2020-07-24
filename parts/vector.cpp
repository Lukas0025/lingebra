/**
 * Linear Algebra CPP lib
 * vector main file
 * @author Lukáš Plevač <lukasplevac@gmail.com>
 * @date   19.7.2020
 * @version 1
 */

#include "vector.h"
#include "macros.h"
#include <algorithm>

template <typename data_t> 
lingebra::vector<data_t>::vector() {
    
    this->mem_init(0);

}

template <typename data_t> 
lingebra::vector<data_t>::vector(unsigned size) {
    
    this->mem_init(size);

}

template <typename data_t> 
lingebra::vector<data_t>::vector(unsigned size, char type) {

    if (!this->mem_init(size)) {
        return;
    }


    if        (type == lingebra_zeros) {
        this->fill(0);
    } else if (type == lingebra_ones)  {
        this->fill(1);
    }
}

template <typename data_t> 
lingebra::vector<data_t>::vector(unsigned size, char type, data_t constant) {
    
    if (!this->mem_init(size)) {
        return;
    }

    this->size = size;

    if (type == lingebra_const) {
        this->fill(constant);
    }
}

template <typename data_t> 
lingebra::vector<data_t>::vector(unsigned size, char type, data_t (*fnc)(unsigned index)) {

    if (!this->mem_init(size)) {
        return;
    }

    this->size = size;

    if (type == lingebra_fnc) {
        this->fill(fnc);
    }
}

template <typename data_t> 
bool lingebra::vector<data_t>::mem_init(unsigned size) {

    unsigned alloc_size = lingebra_alloc_size + size;

    this->data_ptr = this->alloc(alloc_size  * sizeof(data_t));

    this->size    = size;
    this->alloced = alloc_size;
    
    if (this->data_ptr == nullptr) {
        this->error = lingebra_error_memory_managment;
        return false;
    }

    return true;
}

template <typename data_t> 
bool lingebra::vector<data_t>::expand(unsigned size) {
    signed new_alloc_size = size - (this->alloced - this->size);

    if (new_alloc_size <= 0) {
        this->error = lingebra_no_error;
        return true;
    }
    
    new_alloc_size += this->alloced + lingebra_alloc_size;

    void *new_ptr = this->re_alloc((void*) this->data_ptr, new_alloc_size);

    if (new_ptr == nullptr) {
        this->error = lingebra_error_memory_managment;
        return false;
    } else {
        this->data_ptr = (data_t*) this->data_ptr;
        this->error = lingebra_no_error;
        return true;
    }
}

template <typename data_t> 
bool lingebra::vector<data_t>::retract() {
    signed new_alloc_size = this->alloced - this->size;

    if (new_alloc_size <= lingebra_alloc_size * 2) {
        this->error = lingebra_no_error;
        return true;
    }

    new_alloc_size = this->alloced - new_alloc_size + lingebra_alloc_size;

    void *new_ptr = this->re_alloc((void*) this->data_ptr, new_alloc_size);

    if (new_ptr == nullptr) {
        this->error = lingebra_error_memory_managment;
        return false;
    } else {
        this->data_ptr = (data_t*) this->data_ptr;
        this->error = lingebra_no_error;
        return true;
    }
}

template <typename data_t> 
void lingebra::vector<data_t>::fill(data_t constant) {
    for (unsigned i = 0; i < this.size; i++) {
        this->data_ptr[i] = constant;
    }
}

template <typename data_t> 
void lingebra::vector<data_t>::fill(data_t (*fce)(unsigned index)) {
    for (unsigned i = 0; i < this.size; i++) {
        this->data_ptr[i] = fce(i);
    }
}

template <typename data_t> 
void lingebra::vector<data_t>::reg_mem_manager(void* (*alloc)(unsigned size), void* (*re_alloc)(void* ptr, unsigned size), void (*un_alloc)(void* ptr)) {
    this->alloc = alloc;
    this->re_alloc = re_alloc;
    this->un_alloc = un_alloc;
}

template <typename data_t> 
bool lingebra::vector<data_t>::reserve(unsigned size) {
    if (!this->expand(size)) {
        return false;
    }
    //shift end pntr
    this->size += size;
}

template <typename data_t> 
data_t lingebra::vector<data_t>::sum() {
    data_t tmp = 0;

    for (unsigned i = 0; i < this->size; i++) {
        tmp += data_ptr[i];
    }

    return tmp;
}

template <typename data_t> 
void lingebra::vector<data_t>::del(unsigned index) {
    for (unsigned i = index; i < this->size - 1; i++) {
        std::swap(this->data_ptr[i], this->data_ptr[i + 1]);
    }

    this->size--;

    #ifdef lingebra_retract_on_del
        this->retract();
    #endif
}

template <typename data_t> 
lingebra::vector<data_t> lingebra::vector<data_t>::cross(vector const &operand) {
    //todo
}

template <typename data_t> 
void lingebra::vector<data_t>::in_cross(vector const &operand) {
    //todo
}

template <typename data_t> 
data_t lingebra::vector<data_t>::dot(vector const &operand) {
    //todo
}

template <typename data_t> 
void lingebra::vector<data_t>::append(data_t element) {
    this->expand(1);
    this->data_ptr[this->size] = element;
    this->size++;
}

template <typename data_t> 
data_t& lingebra::vector<data_t>::operator [](int index) {
    return data_ptr[index];
}