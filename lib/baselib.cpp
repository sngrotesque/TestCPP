#include "baselib.hpp"

void printHexArray(uint8_t *data, size_t len, uint32_t num, bool newline, bool tableChar)
{
    for(size_t x = 0; x < len; ++x) {
        if(tableChar && ((x) % num == 0)) printf("\t");

        printf("%02x", data[x]);

        if((x + 1) % num) printf(" ");
        else printf("\n");
    }
    if(newline) printf("\n");
}
