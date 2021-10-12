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
    bool nmi_pending : 1; // Stores if there's a pending nmi

    uint8_t (*readByte)(uint16_t address);
    void (*writeByte)(uint16_t address, uint8_t data);
} z80_t;

// initialize a new z80 cpu instance
void z80_init(z80_t *cpu, uint8_t (*r)(uint16_t), void (*w)(uint16_t, uint8_t));
// reset an existing z80 cpu instance
void z80_reset(z80_t *cpu);
// execute instructions for at least 'ticks', but at least one, return executed ticks
uint32_t z80_exec(z80_t* cpu, uint32_t num_ticks);

void z80_init(z80_t *cpu, uint8_t (*r)(uint16_t addr), void (*w)(uint16_t addr, uint8_t byte)) {
    cpu->readByte = r;
    cpu->writeByte = w;
    cpu->af = (z80_reg) { .word = 0x0 };
}

void z80_reset(z80_t *cpu) {
    (void) cpu;
    assert(false && "TODO: z80_reset()\n");
}

uint32_t z80_exec(z80_t* cpu, uint32_t num_ticks) {
    uint32_t ticks = 0;
    uint16_t pc = cpu->pc;
    uint8_t opcode;
    (void) pc;
    (void) opcode;
    do {
        // fetch next opcode byte
        assert(false && "opcode = memory[pc++];");
        assert(false && "instruction = decode(opcode);");
        assert(false && "execute(instruction);");
    } while (ticks < num_ticks);
    return 0;
}

#endif