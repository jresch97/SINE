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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <examples/int.h>
#include <examples/string.h>

#include "hash_table.h"

int main(void)
{
        cos_int i, j;
        cos_string s;
        sine_hash_table string_to_int;

        if (!cos_init()) return EXIT_FAILURE;

        s = cos_new(COS_STRING, "Hello");
        i = cos_new(COS_INT, 5);

        string_to_int = sine_hash_table_new();
        assert(string_to_int);

        sine_hash_table_insert(string_to_int, cos_ref(s), cos_ref(i));

        if (sine_hash_table_lookup(string_to_int, s, &j)) {
                printf("i->val=%d, j->val=%d\n", i->val, j->val);
        } else  printf("Not found.");

        cos_deref_many(3, i, j, s);
        cos_deref(string_to_int);

        cos_term();

        return EXIT_SUCCESS;
}