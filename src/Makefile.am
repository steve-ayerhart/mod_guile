ACLOCAL_AMFLAGS = -I m4

moddir = @APACHE_MODULEDIR@
mod_LTLIBRARIES = mod_guile.la

mod_guile_la_SOURCES = apache_guile.h mod_guile.c

mod_guile_la_CFLAGS = @GUILE_CFLAGS@ @APACHE_CFLAGS@ @APACHE_INCLUDES@
mod_guile_la_LDFLAGS = -module @GUILE_LDFLAGS@ @APACHE_LDFLAGS@
mod_guile_la_LIBS = @APACHE_LIBS@
