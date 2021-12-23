#ifndef Z80_H
#define Z80_H

// Header-only Z80 CPU emulator written in C.

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

// Status indicator flags
#define Z80_C_Flag (1<<0) // Carry
#define Z80_N_Flag (1<<1) // Substract
#define Z80_P_Flag (1<<2) // Parity or Overflow
#define Z80_V_Flag Z80_P_Flag //
#define Z80_F3_Flag (1<<3) // Undocumented flag, copy of bit 3
#define Z80_H_Flag (1<<4) // Half Carry
#define Z80_F5_Flag (1<<5) // Undocumented flag, copy of bit 5
#define Z80_Z_Flag (1<<6) // Zero
#define Z80_S_Flag (1<<7) // Sign

typedef enum {
    NOP = 0x0,
    SUB_A = 0x97,
    DI = 0xf3
} Opcode;

/* extract 16-bit value from 64-bit register bank */
// #define _G16(bank,shift) (((bank)>>(shift))&0xFFFFULL)

// #define _S_WZ(val) _S16(r1,_WZ,val)
// #define _G_WZ() _G16(r1,_WZ)

// /* set 16-bit address bus pins */
// #define _SA(addr) pins=(pins&~0xFFFFULL)|((addr)&0xFFFFULL)
// /* memory read machine cycle */
// #define READ_MR(addr,data) _SA(addr); _TWM(3,Z80_MREQ|Z80_RD); data=_GD()
/* read 16-bit immediate value (also update WZ register) */
// #define READ_IMM16(data) { uint8_t w,z; READ_MR(pc++, z); READ_MR(pc++,w); data = (w<<8) | z; _S_WZ(data); }

typedef union {
    uint16_t word;
    struct {
        uint8_t low; // low byte
        uint8_t high; // high byte
    } byte;
} z80_reg;

typedef struct {
    //
    // SP: Stack Pointer
    z80_reg af; // Register AD (Accumulator + Flags)
    z80_reg bc; // Register BC (B + C)
    z80_reg de; // Register DE (D + E)
    z80_reg hl; // Register HL (H + L)
    uint16_t sp; // Stack Pointer
    uint16_t pc; // Program Counter
    uint16_t ix, iy; // Index or basr register for 8-bit immediate offsets
    uint8_t i; // Interrupt vector base register
    uint8_t r; // DRAM refresh counter;
    uint8_t flags; // |S|Z|-|H|-|P/V|N|C|
    z80_reg _af; // Alternate (or shadow) accumulator and flags
    z80_reg _bc, _de, _hl; // Alternate (or shadow) registers

    uint16_t memory_ptr;

    bool halted : 1; // CPU is halted
    uint8_t interrupt_mode;
    bool interrupt_pending : 1; // Stores if there's a pending interrupt
    uint8_t interrupt_delay;
    bool nmi_pending : 1; // Stores if there's a pending nmi

    uint8_t (*readByte)(uint16_t address); // user function to read from memory
    void (*writeByte)(uint16_t address, uint8_t data); // same for writing to memory
    uint8_t (*port_in)(void *, uint8_t);
    void (*port_out)(void *, uint8_t, uint8_t);

    // TODO: Same for writing to port
    void *userdata; // user costumer data (no idea what this does mean)

    unsigned long cycles; // cycle count
} z80_t;

// initialize a new z80 cpu instance
void z80_init(z80_t *cpu, uint8_t (*r)(uint16_t), void (*w)(uint16_t, uint8_t));
// reset an existing z80 cpu instance
void z80_reset(z80_t *cpu);
// execute instructions for at least 'ticks', but at least one, return executed ticks
uint32_t z80_exec(z80_t *cpu, uint32_t num_ticks);
// TODO: maybe this approach is better
void z80_step(z80_t *cpu, uint8_t opcode);
void z80_debug_output(z80_t *cpu, bool print_disassembly);

#endif
