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

#ifndef SINE_HASHTAB_H
#define SINE_HASHTAB_H

#include <cosine.h>

#define SINE_HASH_TABLE_TYPE       (sine_hash_table_class_get())
#define SINE_HASH_TABLE_CLASS_NAME "HashTable"
#define SINE_HASH_TABLE(obj)       ((sine_hash_table)obj)
#define SINE_HASH_TABLE_CLASS(cls) ((sine_hash_table_class)cls)

typedef struct sine_hash_table_class_s {
        struct cos_object_class_s cls;
} *sine_hash_table_class;

typedef struct sine_hash_table_entry_s {
        struct sine_hash_table_entry_s *next;
        void                           *key, *value;
} sine_hash_table_entry;

typedef struct sine_hash_table_s {
        struct cos_object_s     obj;
        size_t                  _len, _cap, _cap_i;
        sine_hash_table_entry **_entries;
} *sine_hash_table;

cos_class       sine_hash_table_class_get();
void            sine_hash_table_class_construct(cos_class cls);
void            sine_hash_table_class_destruct(cos_class cls);
void            sine_hash_table_construct(cos_object obj, cos_values vals);
void            sine_hash_table_destruct(cos_object obj);
sine_hash_table sine_hash_table_new();
cos_object      sine_hash_table_insert(sine_hash_table table,
                                       void           *key,
                                       void           *value);
cos_object      sine_hash_table_remove(sine_hash_table table, void *key);
int             sine_hash_table_lookup(sine_hash_table table,
                                       void           *key,
                                       void           *out);


#endif