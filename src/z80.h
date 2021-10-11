#ifndef Z80_H
#define Z80_H

// Header-only Z80 CPU emulator written in C.

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t af, bc, de, hl, sp, pc;
    uint16_t ix, iy;
    uint8_t i, r;
    uint16_t _af, _bc, _de, _hl;
} z80_t;

// initialize a new z80 cpu instance
void z80_init(z80_t *cpu);
// reset an existing z80 cpu instance
void z80_reset(z80_t *cpu);

#endif