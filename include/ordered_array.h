#ifndef _ORDERED_ARRAY_H_
#define _ORDERED_ARRAY_H_

#include "system.h"
// ordered_array.c -- Implementation for creating, inserting and deleting
//                    from ordered arrays.
//                    Written for JamesM's kernel development tutorials.

char standard_lessthan_predicate(void*  a, void*  b)
{
    return (a<b)?1:0;
}

ordered_array_t create_ordered_array(unsigned int max_size, lessthan_predicate_t less_than)
{
    ordered_array_t to_ret;
    to_ret.array = (void*)kmalloc(max_size*sizeof(void* ));
    memset(to_ret.array, 0, max_size*sizeof(void* ));
    to_ret.size = 0;
    to_ret.max_size = max_size;
    to_ret.less_than = less_than;
    return to_ret;
}

ordered_array_t place_ordered_array(void *addr, unsigned int max_size, lessthan_predicate_t less_than)
{
    ordered_array_t to_ret;
    to_ret.array = (void* *)addr;
    memset(to_ret.array, 0, max_size*sizeof(void* ));
    to_ret.size = 0;
    to_ret.max_size = max_size;
    to_ret.less_than = less_than;
    return to_ret;
}

void destroy_ordered_array(ordered_array_t *array)
{
//    kfree(array->array);
}

void insert_ordered_array(void*  item, ordered_array_t *array)
{
    ASSERT(array->less_than);
    unsigned int iterator = 0;
    while (iterator < array->size && array->less_than(array->array[iterator], item))
        iterator++;
    if (iterator == array->size) // just add at the end of the array.
        array->array[array->size++] = item;
    else
    {
        void*  tmp = array->array[iterator];
        array->array[iterator] = item;
        while (iterator < array->size)
        {
            iterator++;
            void*  tmp2 = array->array[iterator];
            array->array[iterator] = tmp;
            tmp = tmp2;
        }
        array->size++;
    }
}

void*  lookup_ordered_array(unsigned int i, ordered_array_t *array)
{
    ASSERT(i < array->size);
    return array->array[i];
}

void remove_ordered_array(unsigned int i, ordered_array_t *array)
{
    while (i < array->size)
    {
        array->array[i] = array->array[i+1];
        i++;
    }
    array->size--;
}

#endif // ORDERED_ARRAY_H
