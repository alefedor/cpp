#ifndef __POSITION_H_
#define __POSITION_H_

struct position_node {
  int x, y;
  struct intrusive_node  node;
};

void remove_position(struct intrusive_list *l, int x, int y);
void add_position(struct intrusive_list *l, int x, int y);
void show_all_positions(struct intrusive_list *l);
void remove_all_positions(struct intrusive_list *l);

#endif