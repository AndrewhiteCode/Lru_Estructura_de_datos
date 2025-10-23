#include "lru.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void push_front(LRU *lru, Node *node) {
    node->prev = NULL;
    node->next = lru->head;
    if (lru->head) lru->head->prev = node;
    lru->head = node;
    if (!lru->tail) lru->tail = node;
}

static void remove_node(LRU *lru, Node *node) {
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    else lru->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else lru->tail = node->prev;
    node->prev = node->next = NULL;
}

static void move_to_front(LRU *lru, Node *node) {
    if (!node || lru->head == node) return;
    remove_node(lru, node);
    push_front(lru, node);
}

static Node *evict_tail(LRU *lru) {
    Node *victima = lru->tail;
    if (!victima) return NULL;
    remove_node(lru, victima);
    return victima;
}


LRU *lru_create(int capacity) {
    if (capacity < 5) capacity = 5; /*CAPACIDAD DE LA LISTA*/
    LRU *lru = (LRU*)calloc(1, sizeof(LRU));
    if (!lru) return NULL;
    lru->capacity = capacity;
    lru->size = 0;
    lru->head = lru->tail = NULL;
    for (int i = 0; i < 26; ++i) lru->index[i] = NULL;
    return lru;
}

void lru_free(LRU *lru) {
    if (!lru) return;
    Node *it = lru->head;
    while (it) {
        Node *nxt = it->next;
        free(it);
        it = nxt;
    }
    free(lru);
}

bool lru_get(LRU *lru, char key) {
    if (!lru || !is_upper_letter(key)) return false;
    Node *node = lru->index[key - 'A'];
    if (!node) return false;
    move_to_front(lru, node);
    return true;
}

int lru_search(LRU *lru, char key) {
    if (!lru || !is_upper_letter(key)) return -1;
    Node *node = lru->index[key - 'A'];
    if (!node) return -1;
    int pos = 1;
    for (Node *it = lru->head; it; it = it->next, ++pos) {
        if (it == node) return pos;
    }
    return -1; /* Si todo falla */
}

bool lru_add(LRU *lru, char key, char *evicted_key) {
    if (!lru || !is_upper_letter(key)) return false;
    if (evicted_key) *evicted_key = '\0';

    Node *node = lru->index[key - 'A'];
    if (node) {
        move_to_front(lru, node);
        return true;
    }

    /* nuevo nodo */
    if (lru->size == lru->capacity) {
        Node *victima = evict_tail(lru);
        if (victima) {
            if (evicted_key) *evicted_key = victima->key;
            lru->index[victima->key - 'A'] = NULL;
            free(victima);
            if (lru->size > 0) lru->size--; /* just in case */
        }
    }

    Node *n = (Node*)calloc(1, sizeof(Node));
    if (!n) return false;
    n->key = key;
    push_front(lru, n);
    lru->index[key - 'A'] = n;
    if (lru->size < lru->capacity) lru->size++;
    return true;
}

void lru_print_all(const LRU *lru) {
    printf("Contenido de la cache: ");
    if (!lru || lru->size == 0) {
        printf("(Vacio)\n");
        return;
    }
    const Node *it = lru->head;
    while (it) {
        printf("%c", it->key);
        if (it->next) printf(" - ");
        it = it->next;
    }
    printf("\n");
}