#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <cstddef>

void* kmalloc(size_t size);
void free(void* ptr);

#endif
