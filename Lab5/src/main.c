#include "../include/clist.h"
#include "../include/position.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned char *loadtext(char *name, int *number){
	FILE *f = fopen(name, "r");
	unsigned char *res = malloc(300*sizeof(char));
	size_t sz = 300, num = 0;
	int x, y, c;
	while (!feof(f)){
		c = fscanf(f, "%d%d", &x, &y);
		if (c != 2)
			break;
		if (num + 6 > sz){
			sz += 300;
			res = realloc(res, sz*sizeof(char));
		}
		bool bb = x < 0;
		if (bb)
			x = -x;
		res[num + 2] = (x << 9) >> 25;
		res[num + 2] |= (bb << 7);
		res[num + 1] = (x << 16) >> 24;
		res[num] = (x << 24) >> 24;
		bb = y < 0;
		if (bb)
			y = -y;
		res[num + 5] = (y << 9) >> 25;
		res[num + 5] |= (bb << 7);
		res[num + 4] = (y << 16) >> 24;
		res[num + 3] = (y << 24) >> 24;
		num+=6;
	}
	*number = num;
	fclose(f);
	return res;
}

unsigned char *loadbin(char *name, int *number){
	FILE *f = fopen(name, "r");
	unsigned char *res = malloc(300*sizeof(char));
	size_t sz = 300, num = 0;
	while (!feof(f)){
		if (num + 6 > sz){
			sz += 300;
			res = realloc(res, sz*sizeof(char));
		}
		if (fread(res + num, 1, 6*sizeof(char), f) == 1);
			num += 6;
	}
	*number = (int)num - 6;
	if (number < 0)
		number = 0;
	fclose(f);
	return res;
}

void savetext(char *name, unsigned char *arr, int num){
	FILE *f = fopen(name, "w");
	int x, y;
	for (int i = 0; i < num; i+= 6){
		x = arr[i] + (arr[i + 1] << 8) + (arr[i + 2] << 16);
		if ((x & (1 << 23)) != 0){
			x ^= (1 << 23);
			x = -x;
		}
		y = arr[i + 3] + (arr[i + 4] << 8) + (arr[i + 5] << 16);
		if ((y & (1 << 23)) != 0){
			y ^= (1 << 23);
			y = -y;
		}
		fprintf(f, "%d %d\n", x, y);
	}
	fclose(f);
}

void savebin(char *name, unsigned char *arr, int num){
	FILE *f = fopen(name, "w");
	fwrite(arr, 1, num*sizeof(char), f);
	fclose(f);
}

void count(struct position_node* p, void* num){
	int *pi = (int*)num;
	(*pi)++;
}

void print(struct position_node* p, void* s){
	printf((char*)s, p -> x, p -> y);
}

void apply(struct intrusive_list *l, void (*op)(struct position_node*, void*), void* arg){
	if (l -> head == NULL)
		return;
	struct intrusive_node *cur = l -> head;
	do{
		op(container_of(cur, struct position_node, node), arg);
		cur = cur -> next;
	}while(cur != l -> head);
}

void make(struct intrusive_list *l, unsigned char *arr, int num){
	int x, y;
	for (int i = num - 6; i >= 0; i-=6){
		x = arr[i] + (arr[i + 1] << 8) + (arr[i + 2] << 16);
		if ((x & (1 << 23)) != 0){
			x ^= (1 << 23);
			x = -x;
		}
		y = arr[i + 3] + (arr[i + 4] << 8) + (arr[i + 5] << 16);
		if ((y & (1 << 23)) != 0){
			y ^= (1 << 23);
			y = -y;
		}
		add_position(l, x, y);
	}
}

int main(int argc, char **argv){
	if (argc < 4)
		return 0;
	struct intrusive_list l;
	init_list(&l);
	unsigned char *arr;
	int *num = malloc(1*sizeof(int));
	if (strcmp(argv[1], "loadtext") == 0){
		arr = loadtext(argv[2], num);
	}else{
		arr = loadbin(argv[2], num);
	}
	make(&l, arr, *num);
	if (strcmp(argv[3], "savetext") == 0){
		savetext(argv[4], arr, *num);
	}else if (strcmp(argv[3], "savebin") == 0){
		savebin(argv[4], arr, *num);
	}else if (strcmp(argv[3], "count") == 0){
		int num = 0;
		apply(&l, count, &num);
		printf("%d\n", num);
	}else{
		apply(&l, print, argv[4]);
		printf("\n");
	}
	free(num);
	free(arr);
	remove_all_positions(&l);
	return 0;
}
