#ifndef ORDER_H
#define ORDER_H

#include "gb.h"

typedef enum {
    ORDER_BUY,
    ORDER_SELL
} order_type_t;

typedef struct ORDER {
    order_type_t type;
    double price;
    double quantity;
    struct ORDER *next;
} order_t;

order_t * order_create(order_type_t type, double price,
    double quantity);
void order_free(order_t *order);

void order_print(const order_t *order);

#endif // ORDER_H
