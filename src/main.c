#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "z80.h"

uint8_t memory[8192]; // 8k of ROM

int dumpMemory() {
    size_t col = 0;
    uint16_t row = 0;
    uint32_t addr = 0;
    fprintf(stdout, "%#04x:\t", row);
    while (addr < (sizeof(memory) / sizeof(memory[0]))) {
        fprintf(stdout, "%#04x ", memory[addr++]);
        col++;
        if (col == 10) {
            row += col;
            col = 0;
            fprintf(stdout, "\n");
            fprintf(stdout, "%#04x:\t", row);
        }
    }
    return (0);
}

int loadROM(char *filename, uint32_t address) {
    FILE *rom = fopen(filename, "rb");
    if (rom == NULL) {
        perror("fopen");
        fprintf(stderr, "Error opening %s\n", filename);
        return (1);
    } else {
        fprintf(stdout, "Burn %s into memory starting at address %#04x:\n", filename, address);
    }

    fread(&memory[address], 1, 0x1000, rom);
    fclose(rom);
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    fprintf(stdout, "Hello, Galaksija!\n");
    loadROM("ROM_A.BIN", 0);
    loadROM("ROM_B.BIN", 4096);
    // dumpMemory();

    return (0);
}