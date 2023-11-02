#ifndef BASELIB
#define BASELIB
#include <iostream>
#include <stdexcept>
#include <fstream>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdbool>

void printHexArray(uint8_t *data, size_t len, uint32_t num, bool newline, bool tableChar);

#endif /* BASELIB */
