#ifndef SINE_DYNARR_H
#define SINE_DYNARR_H

#include <cosine.h>

typedef struct sine_dynamic_array_s {
        struct cos_object_s obj;
        size_t              len, cap;
        void               *data;
} *sine_dynamic_array;

#endif