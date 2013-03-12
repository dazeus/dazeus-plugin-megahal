CFLAGS = -I../libdazeus/include -Wall
LDFLAGS = -L../libdazeus/lib -ldazeus

dazeus-plugin-megahal: dazeus-plugin-megahal.o megahal.o
	$(CC) -o dazeus-plugin-megahal dazeus-plugin-megahal.o megahal.o $(LDFLAGS)

dazeus-plugin-megahal.o: dazeus-plugin-megahal.c
	$(CC) -c -o dazeus-plugin-megahal.o dazeus-plugin-megahal.c $(CFLAGS)

megahal.o: megahal.c megahal.h
	$(CC) -c -o megahal.o megahal.c $(CFLAGS)

.PHONY : clean distclean
clean:
	rm -f megahal.o dazeus-plugin-megahal.o

distclean: clean
	rm -f dazeus-plugin-megahal
