#include "strategy.h"
#include "config.def.h"

static void usage(const char *prog) {
    fprintf(stderr,
        "Usage: %s [-c center] [-l levels] [-s spacing] [-q quantity] [-d]\n", prog);
    exit(1);
}

int main(int argc, char *argv[]) {
    double center = DEFAULT_CENTER;
    int levels = DEFAULT_LEVELS;
    double spacing = DEFAULT_SPACING;
    double quantity = DEFAULT_QUANTITY;

    int opt, debug = 0, tick = 0;
    while ((opt = getopt(argc, argv, "c:l:s:q:dh")) != -1) {
        switch (opt) {
        case 'c': center = atof(optarg); break;
        case 'l': levels = atoi(optarg); break;
        case 's': spacing = atof(optarg); break;
        case 'q': quantity = atof(optarg); break;
        case 'd': ++debug; break;
        case 'h': default: usage(argv[0]);
        }
    }

    strategy_t *strategy = strategy_create(center,
        levels, spacing, quantity);
    if (strategy == NULL) {
        fputs("Failed to initialize strategy.\n", stderr);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), stdin)) {
        double price = atof(line);
        printf("\nTICK %d @ %.2f\n", ++tick, price);
        strategy_on_tick(strategy, price);
        if (debug > 0) {
            strategy_print_status(strategy);
        }
        fflush(stdout);
    }

    strategy_free(strategy);
    return 0;
}
