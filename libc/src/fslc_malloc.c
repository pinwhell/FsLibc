#include "fslc_stdlib.h"
#include "fslc_malloc.h"

void initialize_bins(struct bin_t *bins)
{
    size_t i;
    size_t chunk_size = 0;
    size_t chunk_increment = CHUNK_MIN_SIZE;

    for (i = 0; i < 64; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^1
    for (; i < 96; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^2
    for (; i < 112; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^3
    for (; i < 120; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^4
    for (; i < 124; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^5
    for (; i < 126; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^6
    for (; i < 128; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }
}

int find_bin_gte(struct bin_t *bins, size_t target)
{
    // based on code @ http://stackoverflow.com/questions/6553970/find-the-first-element-in-an-array-that-is-greater-than-the-target

    int low = 0;
    int high = MALLOC_BIN_COUNT;
    while (low != high)
    {
        int mid = (low + high) >> 1;
        if (bins[mid].size < target)
        {
            /* This index, and everything below it, must not be the first element
             * greater than or equal of what we're looking for because this element
             * is smaller than the element.
             */
            low = mid + 1;
        }
        else
        {
            /* This element is larger than the element, so anything after it can't
             * be the first element that's larger.
             */
            high = mid;
        }
    }
    /* Now, low and high both point to the element in question. */
    return low;
}