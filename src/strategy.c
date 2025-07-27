#include "strategy.h"

strategy_t * strategy_create(double center, int levels,
        double spacing, double quantity) {
    strategy_t *strategy = malloc(sizeof(strategy_t));
    if (strategy == NULL) return NULL;
    strategy->center = center;
    strategy->levels = levels;
    strategy->spacing = spacing;
    strategy->quantity = quantity;
    strategy->orders = book_create();
    strategy->realized_pnl = 0;
    strategy->quantity_held = 0;

    for (int i = 1; i <= levels; ++i) {
        double buy_price = center - i * spacing;
        double sell_price = center + i * spacing;
        if (!book_contains_order(strategy->orders, buy_price, ORDER_BUY)) {
            book_add_order(strategy->orders,
                order_create(ORDER_BUY, buy_price, quantity));
        }
        if (!book_contains_order(strategy->orders, sell_price, ORDER_SELL)) {
            book_add_order(strategy->orders,
                order_create(ORDER_SELL, sell_price, quantity));
        }
    }
    return strategy;
}

void strategy_free(strategy_t *strategy) {
    if (strategy == NULL) return;
    book_free(strategy->orders);
    free(strategy);
}

void strategy_on_tick(strategy_t *strategy, double price) {
    order_t *curr = strategy->orders->head;
    while (curr) {
        if ((curr->type == ORDER_BUY && price <= curr->price) ||
            (curr->type == ORDER_SELL && price >= curr->price)) {
            printf("Filled %s %.2f x %.2f\n",
                   curr->type == ORDER_BUY ? "BUY" : "SELL",
                   curr->price, curr->quantity);
            if (curr->type == ORDER_BUY) {
                strategy->quantity_held += curr->quantity;
                strategy->realized_pnl -= curr->price * curr->quantity;
                double new_sell = curr->price + 2 * strategy->spacing;
                if (!book_contains_order(strategy->orders, new_sell, ORDER_SELL)) {
                    book_add_order(strategy->orders,
                        order_create(ORDER_SELL, new_sell, curr->quantity));
                }
            } else {
                strategy->quantity_held -= curr->quantity;
                strategy->realized_pnl += curr->price * curr->quantity;
                double new_buy = curr->price - 2 * strategy->spacing;
                if (!book_contains_order(strategy->orders, new_buy, ORDER_BUY)) {
                    book_add_order(strategy->orders,
                        order_create(ORDER_BUY, new_buy, curr->quantity));
                }
            }

            order_t *filled = book_remove_order(strategy->orders,
                curr->price, curr->type);
            order_free(filled);
            curr = strategy->orders->head;
        } else {
            curr = curr->next;
        }
    }
}

void strategy_print_status(strategy_t *strategy) {
    printf("Total PnL: %.2f\n", strategy->realized_pnl);
    printf("Qty Held: %.2f\n", strategy->quantity_held);
    printf("Open Orders:\n");
    book_print(strategy->orders);
}
