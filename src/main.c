#include <stdlib.h>
#include <stdio.h>

int loadROM(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("fopen");
        fprintf(stderr, "Error opening %s\n", filename);
        return (1);
    }

    unsigned char byte;
    size_t col = 0;
    while (fread(&byte, 1, sizeof(byte), fp) == 1) {
        fprintf(stdout, "%#04x ", byte);

        col++;
        if (col == 10) {
            col = 0;
            fprintf(stdout, "\n");
        }

    }

    fclose(fp);

    return (0);
}



int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    fprintf(stdout, "Hello, Galaksija!\n");
    loadROM("galaksija.rom");

    return 0;
}