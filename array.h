#ifndef SINE_ARRAY_H
#define SINE_ARRAY_H

#include <cosine.h>

typedef struct sine_array_s {
        struct cos_object_s obj;
        size_t              len;
        int                 type;
        union {
                void      **ptrs;
                cos_object *objs;
                int       **ints;
        } data;
} sine_array;

#endif