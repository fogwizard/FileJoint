all: FileJoint

DESTDIR ?=
PREFIX  ?= /usr/local
BINDIR  ?= $(PREFIX)/bin

OBJS += src/dictionary.c
OBJS += src/FileJoint.c
OBJS += src/iniparser.c
OBJS += src/ini.c
OBJS += src/log.c

FileJoint: $(OBJS)
	gcc -o $@ $^
clean:
	rm -rf src/*.o
install: FileJoint
	install -d $(DESTDIR)$(BINDIR)
	@set -ex ; for t in $^ ; do \
		install -m0755 $$t $(DESTDIR)$(BINDIR)/$$t ; \
	done
