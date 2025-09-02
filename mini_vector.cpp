#include <iostream>
#include "mini_vector.hpp"

void vector_init(MiniVector& little, int capacity){
    little.size = 0;
    little.capacity = capacity;
    char *ptr = new char[capacity];
    little.elements = ptr;
}

void vector_init_fill(MiniVector& little, int capacity, char init_character){
    little.capacity = capacity;
    little.size = capacity;
    char *ptr = new char[capacity];
    little.elements = ptr;
    for( int i = 0; i < capacity; ++i ){
        *(ptr+i) = init_character;
    }
}

void vector_print(MiniVector& little){
    if( little.size <= 0 ){
        std::cout<< "Vector elements: no elements in vector." << std::endl;
        return;
    }
    std::cout<< "Vector elements: ";
    for( int i = 0; i < little.size-1; ++i ){
        std::cout<< *(little.elements+i) << ", ";
    }
    std::cout<< *(little.elements+little.size-1) << std::endl;
}

void vector_destroy(MiniVector& little){
    delete[] little.elements;
    // delete little;
}

void vector_expand(MiniVector& little, int new_capacity){
    if( new_capacity <= little.capacity ){
        std::cout<< "Cannot shrink vector: new capacity is lower than current." << std::endl;
        return;
    }
    little.capacity = new_capacity;
    char *new_ptr = new char[new_capacity];
    for( int i = 0 ; i < little.size; i++ ){
        *(new_ptr+i) = *(little.elements+i);
    }
    delete[] little.elements;
    little.elements = new_ptr;
}

void vector_shrink(MiniVector& little, int new_capacity){
    if( new_capacity >= little.capacity ){
        std::cout<< "Cannot shrink vector: new capacity is greater than current." << std::endl;
        return;
    }
    if( new_capacity < little.size ){
        std::cout<< "Cannot shrink vector: there are elements that would be lost in the process." << std::endl;
        return;
    }
    little.capacity = new_capacity;
    char *new_ptr = new char[new_capacity];
    for( int i = 0 ; i < little.size; i++ ){
        *(new_ptr+i) = *(little.elements+i);
    }
    delete[] little.elements;
    little.elements = new_ptr;
}

void vector_add(MiniVector& little, char new_el){
    if( little.size == little.capacity){
        vector_expand(little, 2*little.capacity);
    }
    *(little.elements+little.size) = new_el;
    little.size++;
    std::cout<< "Added " << new_el << std::endl;
}

void vector_clear(MiniVector& little){
    vector_destroy(little);
    vector_init(little, INIT_CAPACITY);
}