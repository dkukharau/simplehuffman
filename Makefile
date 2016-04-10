.PHONY: all clean

prefix = /usr/
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin/
srcdir = src/

DESTDIR = /

SOURCE_PATH = $(srcdir)
BUILD_PATH = obj/
CFLAGS = -g -std=c99 -O3
CC = gcc
OBJS = main.o tree.o heap.o huff.o
EXE = huff


OBJS_PATH = $(addprefix $(BUILD_PATH), $(OBJS))
EXE_PATH = $(BUILD_PATH)huff

all: $(BUILD_PATH) $(EXE_PATH)

install: all
	mkdir -p $(DESTDIR)$(bindir)
	cp $(EXE_PATH) $(DESTDIR)$(bindir)

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(EXE_PATH): $(OBJS_PATH)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_PATH)%.o: $(SOURCE_PATH)%.c $(BUILD_PATH)%.d
	$(CC) $(CFLAGS) $< -c -o $@

$(BUILD_PATH)%.d: $(SOURCE_PATH)%.c
	$(CC) -MT $(BUILD_PATH)$*.o -MM -MF $@ $<

include $(wildcard $(BUILD_PATH)/*.d)

.PRECIOUS: $(BUILD_PATH)%.d

clean:
	rm -rf $(BUILD_PATH)
