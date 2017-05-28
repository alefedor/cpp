#include <stdlib.h>
#include <string.h>
#include "../include/bmp.h"

int main(int argc, char **argv){
    if (argc < 8){
        printf("Too few arguments\n");
        return -1;
    }
    bitmap_t b;
    if (strcmp(argv[1], "crop-rotate") == 0){
        unsigned int w, h, x, y;
        x = atoi(argv[4]);
        y = atoi(argv[5]);
        w = atoi(argv[6]);
        h = atoi(argv[7]);
        load_bmp(argv[2], &b);
        y = b.h - h - y;
        unsigned char *arr;
        arr = crop(&b, x, y, w, h);
        arr = rotate(arr, w, h);
        save_bmp(argv[3], &b, arr, h, w);
        free(arr);
        clear_bitmap(&b);
    }
    return 0;
}
