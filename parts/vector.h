/**
 * Linear Algebra CPP lib
 * vector header file
 * @author Lukáš Plevač <lukasplevac@gmail.com>
 * @date   19.7.2020
 * @version 1
 */

#include <cstdlib>
#include "macros.h"

#ifndef lingebra_vector
    #define lingebra_vector

    namespace lingebra {

        template <typename data_t> 
        class vector {
            private:
                data_t     *data_ptr;
                unsigned    size;
                unsigned    alloced;
                char        error = lingebra_no_error;
                void        fill(data_t constant);
                void        fill(data_t (*fce)(unsigned index));
                /* low lovel mem managment */
                void*       (*alloc)(unsigned size)               = malloc;
                void*       (*re_alloc)(void* ptr, unsigned size) = realloc;
                void        (*un_alloc)(void* ptr)                = free;
                /*  top level mem managment */
                bool        mem_init(unsigned size);
                bool        expand(unsigned size);
                bool        retract();

            public:
                            /**
                             * Create lingebra::vector object and pre-alloc lingebra_alloc_size (macro) space for elements
                             * @return lingebra::vector object
                             * @post in this->error is status of this operation
                             */
                            vector();

                            /**
                             * Create lingebra::vector object and pre-alloc size space for elements
                             * @param unsigned size - size of pre-alloc space for elements
                             * @return lingebra::vector object
                             * @post in this->error is status of this operation
                             */
                            vector(unsigned size);

                            /**
                             * Create lingebra::vector object and fill with number of size elements by type (lingebra_ones, lingebra_zeros)
                             * @param unsigned size - number of elements
                             * @param char     type - type of elements (lingebra_ones, lingebra_zeros)
                             * @return lingebra::vector object
                             * @post in this->error is status of this operation
                             */
                            vector(unsigned size, char type);
                            
                            /**
                             * Create lingebra::vector object and fill with number of size constants
                             * @param unsigned size     - number of elements
                             * @param char     type     - type of elements (lingebra_const)
                             * @param data_t   constant - number for fill
                             * @return lingebra::vector object
                             * @post in this->error is status of this operation
                             */
                            vector(unsigned size, char type, data_t constant);

                            /**
                             * Create lingebra::vector object and fill with number of size values form fce(index)
                             * @param unsigned                     size     - number of elements
                             * @param char                         type     - type of elements (lingebra_const)
                             * @param data_t(*)(unsigned index)    fnc      - function for filling it will by use as data[index] = fnc(index)
                             * @return lingebra::vector object
                             */
                            vector(unsigned size, char type, data_t (*fnc)(unsigned index));

                            /**
                             * register new memory manager for vector
                             * @param void*(*)(unsigned size)             alloc     - function for alloc    (default is malloc)
                             * @param void*(*)(void* ptr, unsigned size)  re_alloc  - function for re-alloc (default is realloc)
                             * @param void(*)(void* ptr)                  un_alloc  - function for un-alloc (default is free)
                             * @return void
                             */
                void        reg_mem_manager(void* (*alloc)(unsigned size), void* (*re_alloc)(void* ptr, unsigned size), void (*un_alloc)(void* ptr));

                            /**
                             * reserve space for size of elements and shift end pointer to end of this space
                             * @param unsigned  size - size of space
                             * @return bool - status of operation
                             * @post in this->error is status of this operation
                             */
                bool        reserve(unsigned size);

                            /**
                             * clac sum of all elemets in vector
                             * @return data_t - sum of elements
                             */
                data_t      sum();
                            
                            /**
                             * delete element on index and re-index vector
                             * @param unsigned index - index of element to delete
                             * @return void
                             * @post in this->error is status of this operation
                             */
                void        del(unsigned index);
                            
                            /**
                             * calc cross product as out = this X operand
                             * @param vector const &     operand - operand for multiply
                             * @return vector - this X operand
                             * @post in this->error is status of this operation
                             */
                vector      cross(vector const &operand);

                            /**
                             * calc cross product as out = this X operand
                             * @param vector const &     operand - operand for multiply
                             * @return vector - this X operand
                             * @post in this->error is status of this operation
                             */
                void        in_cross(vector const &operand);

                            /**
                             * calc dot product as out = this * operand
                             * @param vector const &     operand - operand for multiply
                             * @return vector - this * operand
                             * @post in this->error is status of this operation
                             */
                data_t      dot(vector const &operand);

                            /**
                             * add element to end of vector and do size++
                             * @param data_t element - element to add
                             * @return void
                             * @post in this->error is status of this operation
                             */
                void        append(data_t element);

                /* operators */
                data_t&     operator[] (int index);
                /*vector      operator + (vector const &operand);
                vector      operator - (vector const &operand);
                vector      operator * (vector const &operand);
                vector      operator / (vector const &operand);
                vector      operator % (vector const &operand);*/
        };

    };
#endif