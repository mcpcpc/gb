#ifndef BOOK_H
#define BOOK_H

#include "gb.h"
#include "order.h"

typedef struct BOOK {
    order_t *head;
} book_t;

book_t *book_create(void);
void book_free(book_t *book);

void book_add_order(book_t *book, order_t *order);
order_t *book_remove_order(book_t *book, double price,
        order_type_t type);
int book_contains_order(book_t *book, double price,
        order_type_t type);
void book_print(const book_t *book);

#endif // BOOK_H