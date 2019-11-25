#ifndef DLLIST_H
#define DLLIST_H

typedef struct Dlelem {
  struct Dlelem *dle_next;
  struct Dlelem *dle_prev;
  void          *dle_val;
  struct Dllist *dle_list;
} Dlelem;

typedef struct Dllist {
  Dlelem *dll_head;
  Dlelem *dll_tail;
} Dllist;
#endif
