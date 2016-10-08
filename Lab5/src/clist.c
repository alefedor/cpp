#include "../include/clist.h"
#include <stddef.h>

void init_list(struct intrusive_list *l){
	l -> head = NULL;
}

void add_node(struct intrusive_list *l, struct intrusive_node *n){
	if (!l -> head){
		l -> head = n;
		n -> next = n;
		n -> prev = n;
		return;	
	}
	struct intrusive_node *t;
	t = l -> head;
	l -> head = n;
	n -> prev = t -> prev;
	t -> prev -> next = n;
	t -> prev = n;
	n -> next = t;
}

void remove_node(struct intrusive_list *l, struct intrusive_node *n){
	if (n -> next == n){
		l -> head = NULL;
	}else{
		n -> next -> prev = n -> prev;
		n -> prev -> next = n -> next;
		if (l -> head == n)
			l -> head = n -> next;
	}	
}

int get_length(struct intrusive_list *l){
	if (!l -> head)
		return 0;
	int res = 0;
	struct intrusive_node *cur = l -> head;
	do{
		res++;
		cur = cur -> next;
	}while(cur != l -> head);
	return res;
}