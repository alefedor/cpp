#include "../include/clist.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct position_node {
  int x, y;
  struct intrusive_node  node;
};

void remove_position(struct intrusive_list *l, int x, int y) {
	struct intrusive_node *cur = l -> head, t;
	struct position_node *p;
	bool del = false;
	if (cur == NULL)
		return;
	int sz = get_length(l);
	while (sz--){
		p = container_of(cur, struct position_node, node);
		if (p -> x == x && p -> y == y)
			del = true;	
		cur = cur -> next;
		if (del){
			remove_node(l, cur -> prev);
			free(p);
			del = false;
		}
	}
}

void add_position(struct intrusive_list *l, int x, int y) {
	struct position_node *p = malloc(sizeof(*p));
	p -> x = x;
	p -> y = y;
	add_node(l, &(p -> node));
}

void show_all_positions(struct intrusive_list *l) {
	struct intrusive_node *cur = l -> head;
	struct position_node *p;
	if (cur == NULL)
		return;
	do{
		p = container_of(cur, struct position_node, node);
		printf("(%d %d) ", p -> x, p -> y);
		cur = cur -> next;
	}while (cur != l -> head);
}

void remove_all_positions(struct intrusive_list *l) {
	struct position_node *p;
	while (l -> head != NULL){
		p = container_of(l -> head, struct position_node, node);
		remove_node(l, l -> head);
		free(p);
	}
}

int main() {
	struct intrusive_list l;
	init_list(&l);
	char c[100];
	int x, y;
	while (true){
		scanf("%s", &c);
		if (strcmp(c, "add") == 0){
			scanf("%d%d", &x, &y);
			add_position(&l, x, y);
		}else
		if (strcmp(c, "rm") == 0){
			scanf("%d%d", &x, &y);
			remove_position(&l, x, y);
		}else
		if (strcmp(c, "rma") == 0){
			remove_all_positions(&l);
		}else
		if (strcmp(c, "exit") == 0){
			break;	
		}else
		if (strcmp(c, "len") == 0){
			printf("%d\n", get_length(&l));
		}else
		if (strcmp(c, "print") == 0){
			show_all_positions(&l);
			printf("\n");
		}else{
			printf("Unknown command\n");
		}
	}
	remove_all_positions(&l);
	return 0;
}
