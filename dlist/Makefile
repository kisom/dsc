TARGET = libdlist.a
MANPAGE = dlist.3
OBJS = dlist.o
LIBDIR = /usr/local/lib
MANDIR = /usr/local/man/man3
CC = clang
LD = clang
CFLAGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align	\
		-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations   \
		-Wnested-externs -Winline -Wno-long-long  -Wunused-variable   \
		-Wstrict-prototypes -Werror -ansi -D_XOPEN_SOURCE=600	 \
		-D_BSD_SOURCE -ansi -static -g
LDFLAGS = -static

$(TARGET): $(OBJS)
	ar -crs $(TARGET) $(OBJS)

all: $(TARGET)

install: $(TARGET)
	install $(TARGET) $(LIBDIR)
	install -m 644 $(MANPAGE) $(MANDIR)

uninstall:
	
clean:
	rm -f *.o $(TARGET) *core* test_dlist *.plist

check: test
	./test_dlist

test: test_dlist.o libdlist.a
	$(CC) -o test_dlist test_dlist.o -L. -ldlist
