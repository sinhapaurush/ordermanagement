#include <stdio.h>
#include <stdlib.h>

struct OrderRecord
{
    int id;
    char *person;
    char *order;
    int qty;
};
struct Node
{
    struct OrderRecord *value;
    struct Node *next;
};