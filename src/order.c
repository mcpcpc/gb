#include "order.h"

order_t * order_create(order_type_t type, double price,
        double quantity) {
    order_t *order = malloc(sizeof(order_t));
    if (order == NULL) return NULL;
    order->type = type;
    order->price = price;
    order->quantity = quantity;
    order->next = NULL;
    return order;
}

void order_free(order_t *order) {
    if (order != NULL) free(order);
}

void order_print(const order_t *order) {
    if (order == NULL) return;
    const char *type_str = order->type == ORDER_BUY
        ? "BUY" : "SELL";
    printf("%s %.2f x %.2f\n", type_str, order->price,
        order->quantity);
}
