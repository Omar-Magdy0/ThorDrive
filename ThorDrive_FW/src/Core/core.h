#pragma once

#include <stdint.h>


// Direction
#define INPUT 0
#define OUTPUT 1 
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3
#define INPUT_ANALOG 4

// values 
#define HIGH 1
#define LOW 0
#define TOGGLE 2

// Macros for bit manipulation
#define SBI(reg, bit) ((reg) |= (1 << (bit)))
#define CBI(reg, bit) ((reg) &= ~(1 << (bit)))
#define TEST(reg, bit) ((reg) & (1 << (bit)))
#define TBI(reg, bit) ((reg) ^= (1 << (bit)))
