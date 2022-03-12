/**
 *
 * Copyright (C) 2022 Jared B. Resch
 *
 * This file is part of SINE.
 * 
 * SINE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * SINE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with SINE. If not, see <https://www.gnu.org/licenses/>.
 *
 */

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