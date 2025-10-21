#ifndef LRU_H
#define LRU_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
    char key;                 /* 'A'..'Z' */
    struct Node *prev, *next;
} Node;

typedef struct {
    int capacity;
    int size;
    Node *head;               /* MRU */
    Node *tail;               /* LRU */
    Node *index[26];          /* index['A'..'Z'] -> Node* */
} LRU;

#endif /* LRU_H */