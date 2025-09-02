#ifndef MINI_VECTOR_HPP
#define MINI_VECTOR_HPP

static const int INIT_CAPACITY = 4;
struct MiniVector{
    char* elements;
    // static constexpr int capacity;
    int capacity;
    int size;
};

void vector_init(MiniVector& little, int capacity);
void vector_init_fill(MiniVector& little, int capacity, char init_character);
void vector_print(MiniVector& little);
void vector_destroy(MiniVector& little);
void vector_expand(MiniVector& little, int new_capacity);
void vector_shrink(MiniVector& little, int new_capacity);


void vector_add(MiniVector& little, char new_el);
void vector_clear(MiniVector& little);

#endif