#ifndef READFUNCS_H
#define READFUNCS_H
#include "nodes/nodes.h"

extern char *lsptok(char *string, int *length);
extern void *nodeRead(bool read_car_only);
extern Node *parsePlanString();

#endif
