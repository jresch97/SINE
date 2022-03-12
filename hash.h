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

#ifndef SINE_HASH_H
#define SINE_HASH_H

size_t sine_djb2(const char *str)
{
        int    c;
        size_t hash;
        while ((c = *str++)) hash = ((hash << 5) + hash) + c;
        return hash;
}

size_t sine_sdbm(const char *str)
{
        int    c;
        size_t hash;
        while ((c = *str++)) hash = (hash << 6) + (hash << 16) - hash + c;
        return hash;
}

#endif