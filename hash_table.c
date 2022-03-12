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

#include <stdlib.h>

#include "hash_table.h"
#include "hash.h"

static const size_t SINE_HASH_TABLE_CAPS[] = {
        53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
        196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
        50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
};

static cos_class g_sine_hash_table_class = NULL;

static sine_hash_table_entry *sine_hash_table_entry_alloc(cos_object key,
                                                          cos_object value)
{
        sine_hash_table_entry *entry = malloc(sizeof(*entry));
        if (!entry) return NULL;
        entry->key   = key;
        entry->value = value;
        entry->next  = NULL;
        return entry;
}

static void sine_hash_table_entry_free(sine_hash_table_entry *entry)
{
        cos_deref(entry->key);
        cos_deref(entry->value);
        free(entry);
}

cos_class sine_hash_table_class_get()
{
        cos_class cls;
        cos_class_spec spec;
        if (g_sine_hash_table_class) return g_sine_hash_table_class;
        if (cos_class_lookup(SINE_HASH_TABLE_CLASS_NAME, &cls)) return cls;
        spec.name        = SINE_HASH_TABLE_CLASS_NAME;
        spec.parent      = COS_OBJECT;
        spec.cls.size    = sizeof(struct sine_hash_table_class_s);
        spec.cls.ctor    = sine_hash_table_class_construct;
        spec.cls.dtor    = sine_hash_table_class_destruct;
        spec.inst.size   = sizeof(struct sine_hash_table_s);
        spec.inst.ctor   = sine_hash_table_construct;
        spec.inst.dtor   = sine_hash_table_destruct;
        spec.inst.params = cos_params_list(0);
        return cos_class_define(&spec);
}

void sine_hash_table_class_construct(cos_class cls)
{
        if (!g_sine_hash_table_class) g_sine_hash_table_class = cls;
        cos_super_class_construct(COS_OBJECT, cls);
}

void sine_hash_table_class_destruct(cos_class cls)
{
        cos_super_class_destruct(COS_OBJECT, cls);
        if (g_sine_hash_table_class == cls) g_sine_hash_table_class = NULL;
}

void sine_hash_table_construct(cos_object obj, cos_values vals)
{
        size_t i;
        sine_hash_table table;
        cos_super_construct(COS_OBJECT, obj);
        table = SINE_HASH_TABLE(obj);
        table->_len = table->_cap_i = 0;
        table->_cap = SINE_HASH_TABLE_CAPS[table->_cap_i];
        table->_entries = malloc(table->_cap * sizeof(*table->_entries));
        for (i = 0; i < table->_cap; i++) table->_entries[i] = NULL;
}

void sine_hash_table_destruct(cos_object obj)
{
        size_t                 i;
        sine_hash_table        table;
        sine_hash_table_entry *curr, *tmp;
        table = SINE_HASH_TABLE(obj);
        for (i = 0; i < table->_cap; i++) {
                curr = table->_entries[i];
                while (curr) {
                        tmp = curr;
                        curr = curr->next;
                        sine_hash_table_entry_free(tmp);
                }
        }
        free(table->_entries);
        cos_super_destruct(COS_OBJECT, obj);
}

sine_hash_table sine_hash_table_new()
{
        return cos_new(SINE_HASH_TABLE_TYPE);
}

static void sine_hash_table_grow(sine_hash_table table)
{

}

static int sine_hash_table_should_grow(sine_hash_table table)
{
        return 0;
}

cos_object sine_hash_table_insert(sine_hash_table table,
                                  void           *key,
                                  void           *value)
{
        size_t hash, i;
        sine_hash_table_entry *curr, *prev;
        cos_object key_obj, value_obj;
        key_obj = COS_OBJECT_CAST(key);
        value_obj = COS_OBJECT_CAST(value);
        hash = cos_object_hash(key_obj);
        i = hash % table->_cap;
        if (sine_hash_table_should_grow(table)) sine_hash_table_grow(table);
        curr = table->_entries[i];
        if (!curr) {
                curr = sine_hash_table_entry_alloc(key_obj, value_obj);
                if (!curr) return NULL;
                table->_entries[i] = curr;
                return value;
        }
        while (curr) {
                if (cos_object_equals(key_obj, curr->key)) {
                        cos_deref(curr->value);
                        curr->value = value;
                        return value;
                }
                prev = curr, curr = curr->next;
        }
        prev->next = sine_hash_table_entry_alloc(key_obj, value_obj);
        if (!prev->next) return NULL;
        return value_obj;
}

cos_object sine_hash_table_remove(sine_hash_table table, void *key)
{
        return NULL;
}

int sine_hash_table_lookup(sine_hash_table table,
                           void           *key,
                           void           *out)
{
        size_t hash, i;
        sine_hash_table_entry *curr;
        hash = cos_object_hash(key);
        i = hash % table->_cap;
        curr = table->_entries[i];
        while (curr) {
                if (cos_object_equals(key, curr->key)) {
                        (*((void**)out)) = cos_ref(curr->value);
                        return 1;
                }
                curr = curr->next;
        }
        return 0;
}