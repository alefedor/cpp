#include <stdio.h>
#include <stdlib.h>
#include "../include/phonebook.h"
#include <string.h>
#include <time.h>

int cmpr(const void *a, const void *b){
    human_t *pa = (human_t*)a;
    human_t *pb = (human_t*)b;
    return strcmp(pa ->family_name, pb -> family_name);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc < 3){
        printf("Too few arguments\n");
        return 0;
    }
    int result;
    phonebook_t book;
    init_phonebook(&book);
    result = load_phonebook_xml(argv[1], &book);
    if (result)
        printf("Loading xml: Failed\n");
    qsort(book.humans, book.size, sizeof(human_t), cmpr);
    print_phonebook(&book);
    gen_phonebook(&book, 1 + rand() % 15);
    result = save_phonebook_xml(argv[2], &book);
    if (result)
        printf("Saving xml: Failed\n");
    clear_phonebook(&book);
    return 0;
}
