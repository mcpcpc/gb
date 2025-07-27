gb
==

*gb* is a real-time, command-line grid trading bot written in C99. It adheres to the Suckless philosophy: simple, modular, and minimal. The bot reads price data from standard input and writes order fills and status updates to standard output. All state is in-memory, and configuration is passed via command-line flags. No sockets, no threads, no dependencies.

Features
--------

- Single static binary
- No external libraries or socket connections
- Fully pipeable: integrates with Unix tools or other processes
- Designed for real-time use

Usage
-----

Run:

    ./gb [options]

Price ticks are fed line-by-line through standard input, and order events are emitted through standard output.

For full command-line options and usage details, see:

    man gb

Example:

    $ echo -e "99\n100\n101" | ./gb -c 100 -l 3 -s 1 -q 0.5

Output:

    TICK 1 @ 99.00
    Filled BUY 99.00 x 0.50

    TICK 2 @ 100.00

    TICK 3 @ 101.00
    Filled SELL 101.00 x 0.50

Build
-----

    make clean && make
    

Produces the `./gb` binary. Requires only a POSIX-compatible C compiler (e.g., `cc` or `clang`).

Backtesting
-----------

Backtesting is not part of this binary and should be done externally (e.g., via Python with `backtesting.py`).

Philosophy
----------

- No bloat. All logic lives in C99 source files under 500 lines.
- No runtime configuration files or databases.
- No sockets, threads, JSON, XML, or other overhead.
- Everything via `stdin` / `stdout`.
