MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST = Imakefile README notebook.man

noinst_PROGRAMS = notebook

notebook_SOURCES = interface.c  notebook.c

INCLUDES = -I$(top_builddir)/lib -I$(top_srcdir)/lib -I$(top_srcdir)/demos/lib $(X_CFLAGS)

LDADD = -L$(top_builddir)/demos/lib/Xmd -lXmd $(top_builddir)/lib/Xm/libXm.la
