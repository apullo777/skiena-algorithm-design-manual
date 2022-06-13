
//  These programs appear in "The Algorithm Design Manual" by Steven Skiena, third edition, Springer, Switzerland 2020.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int item_type;

typedef struct list {
    item_type item;         /* data item */
    struct list *next;      /* point to successor */
} list;

list *init_list(void) {
    return(NULL);
}

bool empty_list(list *l) {
    if (l == NULL) {
        return (true);
    } else {
        return (false);
    }
}

list *search_list(list *l, item_type x) {
    if (l == NULL) {
        return(NULL);
    }

    if (l->item == x) {
        return(l);
    } else {
        return(search_list(l->next, x));
    }
}

void insert_list(list **l, item_type x) {
    list *p;    /* temporary pointer */

    p = malloc(sizeof(list));
    p->item = x;
    p->next = *l;
    *l = p;
}

list *item_ahead(list *l, list *x) {
    if ((l == NULL) || (l->next == NULL)) {
        return(NULL);
    }

    if ((l->next) == x) {
        return(l);
    } else {
        return(item_ahead(l->next, x));
    }
}

void print_list(list *l) {
    while (l != NULL) {
        printf("%d ", l->item);
        l = l->next;
    }
    printf("\n");
}

void delete_list(list **l, list **x) {
    list *p;            /* item pointer */
    list *pred;         /* predecessor pointer */

    p = *l;
    pred = item_ahead(*l, *x);

    if (pred == NULL) { /* splice out of list */
        *l = p->next;
    } else {
        pred->next = (*x)->next;
    }
    free(*x);           /* free memory used by node */
}

int main(void) {
    char c;             /* input character */
    item_type d;        /* input item */
    list *l;            /* list under construction */
    list *tmp;          /* returned list from search */

    l = init_list();

    while (scanf("%c", &c) != EOF) {
        if (tolower(c) == 'p') {
            print_list(l);
        }

        if (tolower(c) == 'i') {
            scanf("%d", &d);
            printf("new item: %d\n", d);
            insert_list(&l, d);
        }

        if (tolower(c) == 's') {
            scanf("%d", &d);
            tmp = search_list(l, d);
            if (tmp == NULL) { 
				printf("item %d not found\n", d);
            } else {
                printf("item %d found\n", d);
            }
        }

        if (tolower(c) == 'd') {
            scanf("%d", &d);
            tmp = search_list(l, d);
            if (tmp == NULL) {
                printf("item to delete %d not found\n", d);
            } else {
                delete_list(&l, &tmp);
                printf("item %d deleted\n", d);
            }
        }
    }
    return 0;
}


