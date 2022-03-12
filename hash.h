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