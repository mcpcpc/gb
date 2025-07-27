#include "book.h"

book_t *book_create(void) {
    book_t *book = malloc(sizeof(book_t));
    if (book == NULL) return NULL;
    book->head = NULL;
    return book;
}

void book_free(book_t *book) {
    if (book == NULL) return;
    order_t *curr = book->head;
    while (curr != NULL) {
        order_t *tmp = curr->next;
        order_free(curr);
        curr = tmp;
    }
    free(book);
}

void book_add_order(book_t *book, order_t *order) {
    if ((book == NULL) || (order == NULL)) return;
    order->next = book->head;
    book->head = order;
}

order_t * book_remove_order(book_t *book, double price,
        order_type_t type) {
    if ((book == NULL) || (book->head == NULL))
        return NULL;
    order_t *prev = NULL;
    order_t *curr = book->head;
    while (curr != NULL) {
        if (curr->price == price && curr->type == type) {
            if (prev != NULL) {
                prev->next = curr->next;
            } else {
                book->head = curr->next;
            }
            curr->next = NULL;
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}

int book_contains_order(book_t *book, double price, 
        order_type_t type) {
    order_t *curr = book->head;
    while (curr != NULL) {
        if (curr->price == price && curr->type == type) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

void book_print(const book_t *book) {
    const order_t *curr = book->head;
    while (curr != NULL) {
        order_print(curr);
        curr = curr->next;
    }
}