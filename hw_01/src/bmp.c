#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bmp.h"

#define BITMAP_FH_SIZE 14
#define BITMAP_I_SIZE 40

static unsigned int readInt(FILE *f, unsigned int num){
    unsigned char c[5];
    memset(c, 0, sizeof(c));
    if (fread(c, num , 1, f) != 1){
        fclose(f);
        exit(1);
    }
    return c[0] + (c[1] << 8) + (c[2] << 16) + (c[3] << 24);
}

static void writeInt(FILE *f, unsigned int num, unsigned int a){
    unsigned char c[5];
    c[0] = (a << 24) >> 24;
    c[1] = (a << 16) >> 24;
    c[2] = (a << 8) >> 24;
    c[3] = a >> 24;
    if (fwrite(c, num, 1, f) != 1){
        fclose(f);
        exit(1);
    }
}

void load_bmp(const char *filename, bitmap_t *b){
    FILE *f = fopen(filename, "r");
    if (!f){
        //printf("Error on opening in_file\n");
        exit(1);
    }
    b -> uniq = readInt(f, 2);
    fseek(f, 16, SEEK_CUR);
    b -> w = readInt(f, 4);
    b -> h = readInt(f, 4);
    fseek(f, 2, SEEK_CUR);
    b -> bitcnt = readInt(f, 2);
    if (fread(b -> info, 24, 1, f) != 1){
        fclose(f);
        exit(1);
    }
    b -> sz = (b -> w * b -> bitcnt) / 8;
    if (b -> sz % 4 != 0)
        b -> sz += 4 - b -> sz % 4;
    b -> sz *= b -> h;
    b -> ps = malloc(sizeof(char) * b -> sz);
    if (fread(b -> ps, b -> sz, 1, f) != 1){
        fclose(f);
        exit(1);
    }
    fclose(f);
}

unsigned char* crop(bitmap_t *b, unsigned int x, unsigned int y, unsigned int w, unsigned int h){
    unsigned char* res = malloc(3 * w * h);
    unsigned int line = b -> w * 3;
    if (line % 4 != 0)
        line += 4 - line % 4;
    for (unsigned int i = 0, pos = 0, npos = 0; i < b -> h; i++, pos += line){
        if (i >= y && i < y + h){
            for (unsigned int j = x; j < x + w; j++, npos += 3)
                memcpy(res + npos, b -> ps + (pos + j * 3), 3);
        }
    }
    return res;
}

unsigned char* rotate(unsigned char *arr, unsigned int w, unsigned int h){
    unsigned char *tmp = malloc(3 * w * h * sizeof(char));
    for (unsigned int i = 0; i < h; i++)
        for (unsigned int j = 0; j < w; j++)
            memcpy(tmp + ((w - j - 1) * h + i) * 3, arr + (i * w + j) * 3, 3);
    free(arr);
    return tmp;
}

void save_bmp(const char *filename, bitmap_t *b, unsigned char *arr, unsigned int w, unsigned int h){
    FILE *f = fopen(filename, "w");
    if (!f){
        //printf("Error on opening out_file\n");
        exit(1);
    }
    unsigned int line = w * 3;
    if (line % 4 != 0)
        line += 4 - line % 4;
    writeInt(f, 2, b -> uniq);
    writeInt(f, 4, BITMAP_FH_SIZE + BITMAP_I_SIZE + line * h);
    writeInt(f, 4, 0);
    writeInt(f, 4, BITMAP_FH_SIZE + BITMAP_I_SIZE);
    writeInt(f, 4, BITMAP_I_SIZE);
    writeInt(f, 4, w);
    writeInt(f, 4, h);
    writeInt(f, 2, 1);
    writeInt(f, 2, b -> bitcnt);
    unsigned int sz = line * h;
    b -> info[4] = (sz << 24) >> 24;
    b -> info[5] = (sz << 16) >> 24;
    b -> info[6] = (sz << 8) >> 24;
    b -> info[7] = sz >> 24;
    if (fwrite(b -> info, 24, 1, f) != 1){
        fclose(f);
        exit(1);
    }
    unsigned char zer[4];
    memset(zer, 0, sizeof(zer));
    for (unsigned int i = 0; i < h; i++){
        if (fwrite(arr + (i * w * 3), w * 3, 1, f) != 1){
            fclose(f);
            exit(1);
        }
        if ((w * 3) % 4 != 0)
            if (fwrite(zer, 4 - (w * 3) % 4, 1, f) != 1){
                fclose(f);
                exit(1);
            }
    }
    fclose(f);
}

void clear_bitmap(bitmap_t *b){
    free(b -> ps);
}

