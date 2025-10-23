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

/* Constructor / destructor */
LRU *lru_create(int capacity);
void lru_free(LRU *lru);

/* Funciones */
bool lru_add(LRU *lru, char key, char *evicted_key);   
bool lru_get(LRU *lru, char key);                      
int  lru_search(LRU *lru, char key);                   
void lru_print_all(const LRU *lru);                    

/* Validadores */
static inline bool is_upper_letter(char c) { return c >= 'A' && c <= 'Z'; }

#endif /* LRU_H */