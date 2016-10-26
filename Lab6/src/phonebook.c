#include <expat.h>
#include <stdio.h>
#include <string.h>
#include "../include/names.h"
#include "../include/phonebook.h"
#include <time.h>


#define BUFFER_SIZE 2000

void push_back_human(phonebook_t *book){
    if (book -> size == book -> capacity){
        book -> capacity *= 2;
        book -> humans = realloc(book -> humans, sizeof(human_t) * book -> capacity);
    }
    book -> humans[book -> size].phones[0][0] = '\0';
    book -> size++;
}

void start_element(void *data, const char *element, const char **attribute) {
    phonebook_t *book = (phonebook_t*)data;
    if (strcmp(element, "human") == 0){
	push_back_human(book);
        char* tmp = malloc(1000);
        strcpy(tmp, attribute[1]);
	char *p = tmp;
        p = strtok(p, " \t");
        strcpy(book -> humans[book -> size - 1].name, p);
	p = strtok(NULL, " \t");
        strcpy(book -> humans[book -> size - 1].middle_name, p);
        p = strtok(NULL, " \t");
        strcpy(book -> humans[book -> size - 1].family_name, p);
    	free(tmp);
    }
}

void end_element(void *data, const char *element) {
    //nothing to do
}

void handle_data(void *data, const char *content, int length) {
    phonebook_t *book = (phonebook_t*)data;
    char* tmp = malloc(length + 1);
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    char *p = strtok(tmp, " \n\t");
    if (p != NULL){
        size_t num;
	for (num = 0; num < 9; num++)
		if (book -> humans[book -> size - 1].phones[num][0] == '\0')
			break;
        strcpy(book -> humans[book -> size - 1].phones[num], p);
    	if (num != 9)
		book -> humans[book -> size - 1].phones[num + 1][0] = '\0';	
    }
    free(tmp);
}

int load_phonebook_xml(const char *filename, phonebook_t *book){
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    char* buff = malloc(BUFFER_SIZE*sizeof(char));
    memset(buff, 0, BUFFER_SIZE);
    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
    XML_SetUserData(parser, book);
    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), BUFFER_SIZE, fp);
        done = len < BUFFER_SIZE;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            free(buff);    
	    return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);
    free(buff);
    return 0;
}

int save_phonebook_xml(const char *filename, phonebook_t *book){
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file for writing\n");
        return 3;
    }
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp, "<phonebook>\n");
    for (size_t i = 0; i < book -> size; i++){
        fprintf(fp, "\t<human name=\"%s %s %s\">\n", book -> humans[i].name,
                                                 book -> humans[i].middle_name,
                                                 book -> humans[i].family_name);
        for (size_t j = 0; j < 10 && book -> humans[i].phones[j][0] != '\0'; j++)
            fprintf(fp, "\t\t<phone>%s</phone>\n", book -> humans[i].phones[j]);
        fprintf(fp, "\t</human>\n");
    }
    fprintf(fp, "</phonebook>");
    fclose(fp);
    return 0;
}

void print_phonebook(phonebook_t *book){
    printf("%u\n", book -> size);
    for (size_t i = 0; i < book -> size; i++){
        printf("name: %s\n", book -> humans[i].name);
        printf("middle name: %s\n", book -> humans[i].middle_name);
        printf("family name: %s\n", book -> humans[i].family_name);
        for (size_t j = 0; j < 10 && book -> humans[i].phones[j][0] != '\0'; j++)
            printf("phone: %s\n", book -> humans[i].phones[j]);
    	if (i + 1 != book -> size)
	    printf("\n");
    }
}

void clear_phonebook(phonebook_t *book){
    free(book -> humans);
    book -> capacity = 0;
    book -> size = 0;
}

void gen_phonebook(phonebook_t *book, size_t sz){
	clear_phonebook(book);
	init_phonebook(book);
        for (size_t i = 0; i < sz; i++){
	    push_back_human(book);
            size_t num = 1 + rand() % 5; // 1-5 phonenumbers
            for (size_t j = 0; j < num; j++){
                size_t len = 5 + rand() % 16; //5-20 length of phone number
                for (size_t k = 0; k < len; k++)
                    book -> humans[i].phones[j][k] = '0' + rand() % 10;
                book -> humans[i].phones[j][len] = '\0';
            }
	    book -> humans[i].phones[num][0] = '\0';
            strcpy(book -> humans[i].name, kNames[rand() % NAMES_CNT]);
            strcpy(book -> humans[i].family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
            strcpy(book -> humans[i].middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
        }
}

void init_phonebook(phonebook_t *book){
	book -> size = 0;
	book -> capacity = 1;
	book -> humans = malloc(sizeof(human_t));
}