#include "lru.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void rstrip(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ' || s[n-1] == '\t')) {
        s[--n] = '\0';
    }
}

static int parse_int(const char *s, int *out) {
    char *end = NULL;
    long v = strtol(s, &end, 10);
    if (end == s || *end != '\0') return 0;
    *out = (int)v;
    return 1;
}

static char to_upper_letter(const char *s) {
    if (!s || !*s) return 0;
    char c = (char)toupper((unsigned char)s[0]);
    return is_upper_letter(c) ? c : 0;
}

void cli_run(void) {
    LRU *lru = NULL;
    char line[256];

    while (fgets(line, sizeof(line), stdin)) {
        rstrip(line);
        if (!*line) continue;

        char *cmd = strtok(line, " \t");
        if (!cmd) continue;

        if (strcmp(cmd, "lru") != 0) {
            printf("Unknown prefix. Use: lru <command>\n");
            continue;
        }

        char *sub = strtok(NULL, " \t");
        if (!sub) {
            printf("Missing command. Try: create | add | search | get | all | exit\n");
            continue;
        }

        if (strcmp(sub, "exit") == 0) {
            if (lru) {
                lru_free(lru);
                lru = NULL;
            }
            printf("Bye!\n");
            break;
        } else if (strcmp(sub, "create") == 0) {
            char *nstr = strtok(NULL, " \t");
            int cap = 0;
            if (!nstr || !parse_int(nstr, &cap) || cap <= 0) {
                printf("Invalid size. Usage: lru create N (N>=5)\n");
                continue;
            }
            if (lru) {
                lru_free(lru);
                lru = NULL;
            }
            lru = lru_create(cap);
            if (!lru) {
                printf("Allocation error\n");
                continue;
            }
            printf("Cache created with size %d\n", lru->capacity);
        } else if (strcmp(sub, "all") == 0) {
            lru_print_all(lru);
        } else if (strcmp(sub, "add") == 0) {
            char *kstr = strtok(NULL, " \t");
            char key = to_upper_letter(kstr);
            if (!key) { printf("Invalid data. Must be A..Z\n"); continue; }
            if (!lru) { printf("Create the cache first with: lru create N\n"); continue; }
            char evicted = '\0';
            int existed = (lru->index[key - 'A'] != NULL);
            if (!lru_add(lru, key, &evicted)) {
                printf("Operation failed\n");
                continue;
            }
            if (existed) {
                printf("Data element %c used\n", key);
            } else {
                if (evicted) {
                    printf("Data element %c deleted\n", evicted);
                }
                printf("Data %c added to cache\n", key);
            }
        } else if (strcmp(sub, "get") == 0) {
            char *kstr = strtok(NULL, " \t");
            char key = to_upper_letter(kstr);
            if (!key) { printf("Invalid data. Must be A..Z\n"); continue; }
            if (!lru) { printf("Create the cache first with: lru create N\n"); continue; }
            if (lru_get(lru, key)) {
                printf("Data element %c used\n", key);
            } else {
                printf("Data element %c not found\n", key);
            }
        } else if (strcmp(sub, "search") == 0 || strcmp(sub, "seach") == 0) {
            char *kstr = strtok(NULL, " \t");
            char key = to_upper_letter(kstr);
            if (!key) { printf("Invalid data. Must be A..Z\n"); continue; }
            if (!lru) { printf("Create the cache first with: lru create N\n"); continue; }
            int pos = lru_search(lru, key);
            if (pos == -1) printf("-1\n");
            else printf("%d\n", pos);
        } else {
            printf("Unknown command: %s\n", sub);
        }
    }

    if (lru) lru_free(lru);
}