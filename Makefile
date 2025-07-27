.POSIX:
.SUFFIXES:

include config.mk

CFLAGS += -std=c99 -Wall -Wextra -Wno-unused-parameter
CFLAGS += -g -Iinclude -Isrc -I.

SRC = src
OBJ = main.o book.o order.o strategy.o

all: gb

gb: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f gb *.o

install:
	mkdir -p $(DESTDIR)$(BINDIR)
	cp -f gb $(DESTDIR)$(BINDIR)
	chmod 755 $(DESTDIR)$(BINDIR)/gb
	mkdir -p $(DESTDIR)$(MANDIR)/man1
	cp -f gb.1 $(DESTDIR)$(MANDIR)/man1
	chmod 644 $(DESTDIR)$(MANDIR)/man1/gb.1

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/gb
	rm -f $(DESTDIR)$(MANDIR)/man1/gb.1

.PHONY: all clean install uninstall
