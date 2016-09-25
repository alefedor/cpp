#ifndef __CLIST_H_
#define __CLIST_H_
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct intrusive_node {
	struct intrusive_node* next;
	struct intrusive_node* prev;
};

struct intrusive_list {
	struct intrusive_node* head;
};

void init_list(struct intrusive_list *l);
void add_node(struct intrusive_list *l, struct intrusive_node *n);
void remove_node(struct intrusive_list *l, struct intrusive_node *n);
int get_length(struct intrusive_list *l);

#endif