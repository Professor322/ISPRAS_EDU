# Installation directory prefix for Debian GNU/Linux
DESTDIR =
# Generic installation directory prefix
PREFIX = $(DESTDIR)/usr

# Where to put binaries on 'make install'?
BINDIR = $(PREFIX)/bin
# Where to put documentation on 'make install'?
DOCDIR = $(PREFIX)/share/doc/lbt
# Where to put manual pages on 'make installman'?
MANDIR = $(PREFIX)/share/man/man1

# Installation commands
INSTALLDIR = install -d
INSTALLBIN = install
INSTALLDATA = install -m 444
RM = rm -f

# GCC (tested with 2.95.4 and 3.0.2)
CXX=g++
CXXFLAGS=$(CFLAGS) -fno-exceptions -fno-rtti
LDFLAGS=
CC=gcc
CFLAGS=-O3 -fomit-frame-pointer

## Compaq C++ V6.3-011 for Digital UNIX V4.0G (Rev. 1530)
#CXX=cxx
#CXXFLAGS=$(CFLAGS) -nocleanup -nortti
#LDFLAGS=
#CC=cc
#CFLAGS=-arch host -tune host -assume trusted_short_alignment -assume noptrs_to_globals -compress -O5 -om -w1 -std strict_ansi_errors

TARGETS = lbt lbt2dot
LBTOBJS = Ltl.o LtlGraph.o BitVector.o lbt.o
L2DOBJS = lbt2dot.o

OBJS = $(LBTOBJS) $(L2DOBJS)

MANPAGES = lbt.1 lbt2dot.1

all: $(TARGETS)

clean:
	$(RM) $(OBJS)
reallyclean: clean
	$(RM) $(TARGETS)

install: $(TARGETS)
	$(INSTALLDIR) $(BINDIR) $(DOCDIR)
	$(INSTALLBIN) lbt lbt2dot $(BINDIR)
	$(INSTALLDATA) doc/* $(DOCDIR)

installman: $(MANPAGES)
	$(INSTALLDIR) $(MANDIR)
	$(INSTALLDATA) $(MANPAGES) $(MANDIR)

lbt: $(LBTOBJS)
	$(CXX) -o $@ $(LBTOBJS) $(LDFLAGS)
lbt2dot: $(L2DOBJS)
	$(CC) -o $@ $(L2DOBJS) $(LDFLAGS)

.C.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.phony: all clean reallyclean install installman
.SUFFIXES:
.SUFFIXES: .C .c .o

Ltl.o LtlGraph.o lbt.o: Ltl.h LtlGraph.h BitVector.h
BitVector.o: BitVector.h
