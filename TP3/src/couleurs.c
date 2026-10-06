#include <stdint.h>
#include <stdio.h>

struct couleur {
    uint8_t rouge;
    uint8_t vert;
    uint8_t bleu;
    uint8_t alpha;
};

int main(void)
{
    const struct couleur couleurs[10] = {
        {0xef, 0x78, 0x12, 0xff}, {0x2c, 0xc8, 0x64, 0xff},
        {0x10, 0x20, 0x30, 0xff}, {0xff, 0x00, 0x00, 0xff},
        {0x00, 0xff, 0x00, 0xff}, {0x00, 0x00, 0xff, 0xff},
        {0x40, 0x80, 0xc0, 0xff}, {0xaa, 0xbb, 0xcc, 0xff},
        {0x12, 0x34, 0x56, 0x80}, {0x01, 0x02, 0x03, 0x00}
    };

    for (int i = 0; i < 10; i++) {
        printf("Couleur %d : R=%u G=%u B=%u A=%u\n", i + 1,
               (unsigned int)couleurs[i].rouge,
               (unsigned int)couleurs[i].vert,
               (unsigned int)couleurs[i].bleu,
               (unsigned int)couleurs[i].alpha);
    }
    return 0;
}