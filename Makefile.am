SUBDIRS = src

ACLOCAL_AMFLAGS = -I m4

moddir = $(prefix)/share/guile/site

SOURCES = mod-guile.scm

GOBJECTS = $(SOURCES:%.scm=%.go)

nobase_mod_DATA = $(SOURCES) $(GOBJECTS)
EXTRA_DIST = $(SOURCES)

CLEAN_FILES = $(GOBJECTS)

GUILE_WARNINGS = -Wunbound-variable -Warity-mismatch -Wformat

SUFFIXES = .scm .go
.scm.go:
	$(top_builddir)/env @GUILE_COMPILE@ $(GUILE_WARNINGS) -o "$@" "$<"
