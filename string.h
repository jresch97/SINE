#ifndef SINE_STRING_H
#define SINE_STRING_H

#include <cosine.h>

typedef struct sine_string_s {
        struct cos_object_s obj;
        size_t              len;
        const char         *str;
} *sine_string;

#endif