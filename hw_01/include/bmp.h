#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct bitmap{
    size_t w, h;
    size_t bitcnt;
    unsigned char info[25];
    unsigned char *ps;
    size_t sz;
    size_t uniq;
} bitmap_t;

void load_bmp(const char *filename, bitmap_t *b);
unsigned char* crop(bitmap_t *b, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
unsigned char* rotate(unsigned char *arr, unsigned int w, unsigned int h);
void save_bmp(const char *filename, bitmap_t *b, unsigned char *arr, unsigned int w, unsigned int h);
void clear_bitmap(bitmap_t *b);
