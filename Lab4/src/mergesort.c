#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int (*cmp_t)(void*, void*);

int cmp_i(void* p1, void* p2){
	int *pa = (int*)p1;
	int *pb = (int*)p2;
	return (*pa - *pb);
}

int cmp_c(void* p1, void* p2){
	char *pa = (char*)p1;
	char *pb = (char*)p2;
	return ((int)*pa - (int)*pb);
}

int cmp_s(void* p1, void* p2){
	char **pa = (char**)p1;
	char **pb = (char**)p2;
	return strcmp(*pa, *pb);
}

void copy(char *p1, char *p2, size_t sz){
	for (int i = 0; i < sz; i++)
		p1[i] = p2[i];
}

void mergesort(void* base, size_t num, size_t sz, cmp_t cmpr){
	if (num == 1)
		return;
	char *p = base;
	char *a = malloc(num * sz);
	for (int i = 0; i < num*sz; i++, p++)
		a[i] = *p;
	int m = num / 2;
	mergesort(a, m, sz, cmpr);
	mergesort(a + m * sz, num - m, sz, cmpr);
	char *p1 = a, *p2 = p1 + sz * m, *e1 = p2, *e2 = p1 + sz*num;
	p = base;
	while (p1 != e1 && p2 != e2){
		if (cmpr(p1, p2) > 0){
			copy(p, p2, sz);
			p2 += sz;
		}else{
			copy(p, p1, sz);
			p1 += sz;
		}
		p += sz;
	}
	while (p1 != e1){
		copy(p, p1, sz);
		p += sz;
		p1 += sz;	
	}
	while (p2 != e2){
		copy(p, p2, sz);	
		p += sz;
		p2 += sz;
	}
	free(a);
}

int main(int argc, char **argv){
	if (argc < 3)
		return 0;
	if (argv[1][0] == 'i'){
		int c[argc - 2];
		for (int i = 0; i < argc - 2; i++){
			c[i] = 0;
			int st = 0;
			if (argv[i + 2][0] == '-')
				st = 1;
			for (int j = st; argv[i + 2][j] != '\0'; j++)
				c[i] = c[i] * 10 + argv[i + 2][j] - '0';
			if (st == 1)
				c[i] = -c[i];
		}
		mergesort(c, argc - 2, sizeof(int), cmp_i);
		for (int i = 0; i < argc - 2; i++)
			printf("%d ", c[i]);
	}else if (argv[1][0] == 'c'){
		char c[argc - 2];
		for (int i = 0; i < argc - 2; i++)
			c[i] = argv[i + 2][0];
		mergesort(c, argc - 2, sizeof(char), cmp_c);
		for (int i = 0; i < argc - 2; i++)
			printf("%c ", c[i]);
	}else{
		mergesort(argv + 2, argc - 2, sizeof(char*), cmp_s);
		for (int i = 2; i < argc; i++)
			printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}
