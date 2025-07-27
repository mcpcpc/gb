#ifndef STRATEGY_H
#define STRATEGY_H

#include "gb.h"
#include "book.h"

typedef struct STRATEGY {
    double center;
    int levels;
    double spacing;
    double quantity;
    book_t *orders;

    double realized_pnl;
    double quantity_held;
} strategy_t;

strategy_t * strategy_create(double center, int levels,
        double spacing, double quantity);
void strategy_free(strategy_t *strategy);

void strategy_on_tick(strategy_t *strategy, double price);
void strategy_print_status(strategy_t *strategy);

#endif // STRATEGY_H
