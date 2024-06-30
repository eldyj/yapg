CC=gcc
PREFIX=/usr/local
all:
	$(CC) -o yapg main.c

install: all
	mv yapg $(PREFIX)/bin
