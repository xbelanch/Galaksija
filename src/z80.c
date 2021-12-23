#include "z80.h"


void z80_init(z80_t *cpu, uint8_t (*r)(uint16_t addr), void (*w)(uint16_t addr, uint8_t byte)) {
    cpu->readByte = r;
    cpu->writeByte = w;
    cpu->port_in = NULL;
    cpu->port_out = NULL;

    cpu->cycles = 0;
    cpu->pc = 0;
    cpu->sp = 0;

    cpu->af = (z80_reg) { .word = 0x0 };
    cpu->af = (z80_reg) { .word = 0x0 };
    cpu->bc = (z80_reg) { .word = 0x0 };
    cpu->de = (z80_reg) { .word = 0x0 };
    cpu->hl = (z80_reg) { .word = 0x0 };

    cpu->interrupt_mode = 0;
    cpu->interrupt_pending = 0;
    cpu->interrupt_delay = 0;
    cpu->halted = 0;
}

void z80_reset(z80_t *cpu) {
    cpu->af = (z80_reg) { .word = 0x0 };
    cpu->bc = (z80_reg) { .word = 0x0 };
    cpu->de = (z80_reg) { .word = 0x0 };
    cpu->hl = (z80_reg) { .word = 0x0 };
    cpu->ix = 0;
    cpu->iy = 0;
    cpu->sp = cpu->pc = 0;
    cpu->_af = cpu->_bc = cpu->_de = cpu->_hl = (z80_reg) { .word = 0x0 };
    cpu->i = cpu->r = 0;
    cpu->interrupt_mode = 0;
    cpu->halted = 0;
}

uint32_t z80_exec(z80_t* cpu, uint32_t num_ticks) {
    uint32_t ticks = 0;
    uint16_t pc = cpu->pc;
    uint16_t jptemp;
    uint8_t opcode;
    do {
        opcode = cpu->readByte(pc);
        // fetch next opcode byte
        // fprintf(stdout, "opcode: %#02x\n", opcode);
        switch(opcode) {
        case NOP: fprintf(stdout, "%#02x ; ;\t\t\t%#02x\n", opcode, pc); pc++; break; // NOP
        case DI: fprintf(stdout, "%#02x: di\t\t Disable interrupts;\t\t\t%#02x\n", opcode, pc); pc++; break;
        case SUB_A: fprintf(stdout, "%#02x: sub a\t\t Clear accumulator;\t\t\t%#02x\n", opcode, pc); pc++; break;
        case 0xc3:
            jptemp = pc;
            uint16_t p = jptemp;
            uint16_t l = cpu->readByte(++jptemp);
            uint16_t h = cpu->readByte(++jptemp);
            pc =  l + (h << 8);
            fprintf(stdout, "%#02x: jp %#02x\t\t; Jump forward to START_2;\t\t\t%#02x\n", opcode, pc, p);
            break;
        case 0xfd:
            fprintf(stdout, "%#02x: FD_PREFIX DONT UNDERSTAND WHAT IS HAPPENING HERE;\t\t\t%#02x\n", opcode, pc); pc++; break;
        case 0x21:
            fprintf(stdout, "%#02x: ld, nn; Load latch address (nn) into HL;\t\t\t%#02x\n", opcode, pc); pc++; break;
        case 0xed: // What the hell it works?
            fprintf(stdout, "%#02x: fetch next opcode;\t\t\t%#02x\n", opcode, pc); pc++;
            opcode = cpu->readByte(pc);
            switch(opcode) {
            case 0x56: fprintf(stdout, "%#02x: im 1\t\t; Set interrupt mode 1;\t\t\t%#02x\n", opcode, pc); pc++; break;
            default: break;
            }
            break;
        default: fprintf(stdout, "%#04x: Unknow opcode\n", opcode); pc++; break;
        }
        // assert(false && "instruction = decode(opcode);");
        // assert(false && "execute(instruction);");
        ticks++;
        // fprintf(stdout, "ticks: %d | num_ticks: %d\n", ticks, num_ticks);
    } while (ticks < num_ticks);
    return 0;
}
