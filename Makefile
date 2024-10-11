# Makefile.in generated by automake 1.11.3 from Makefile.am.
# example/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
# 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011 Free Software
# Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.




pkgdatadir = $(datadir)/pbc
pkgincludedir = $(includedir)/pbc
pkglibdir = $(libdir)/pbc
pkglibexecdir = $(libexecdir)/pbc
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = arm-apple-darwin23.0.0
host_triplet = arm-apple-darwin23.0.0
noinst_PROGRAMS = test_ns_ibe_waters$(EXEEXT) \
	test_ns_ibe_waters_addClient$(EXEEXT) \
	test_mst_ibe_waters$(EXEEXT) \
	test_mst_ibe_addClient_wo_vf$(EXEEXT) \
	test_mst_ibe_addClient_w_vf$(EXEEXT) \
	test_waters_multithreads$(EXEEXT)
subdir = example
DIST_COMMON = README $(srcdir)/Makefile.am $(srcdir)/Makefile.in
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
PROGRAMS = $(noinst_PROGRAMS)
am_test_mst_ibe_addClient_w_vf_OBJECTS =  \
	test_mst_ibe_waters_addClient_w_vf.$(OBJEXT) \
	sim_mst_ibe.$(OBJEXT) waters_ibe.$(OBJEXT) \
	file_process.$(OBJEXT)
test_mst_ibe_addClient_w_vf_OBJECTS =  \
	$(am_test_mst_ibe_addClient_w_vf_OBJECTS)
test_mst_ibe_addClient_w_vf_LDADD = $(LDADD)
test_mst_ibe_addClient_w_vf_DEPENDENCIES = ../libpbc.la
am_test_mst_ibe_addClient_wo_vf_OBJECTS =  \
	test_mst_ibe_waters_addClient_wo_vf.$(OBJEXT) \
	sim_mst_ibe.$(OBJEXT) waters_ibe.$(OBJEXT) \
	file_process.$(OBJEXT)
test_mst_ibe_addClient_wo_vf_OBJECTS =  \
	$(am_test_mst_ibe_addClient_wo_vf_OBJECTS)
test_mst_ibe_addClient_wo_vf_LDADD = $(LDADD)
test_mst_ibe_addClient_wo_vf_DEPENDENCIES = ../libpbc.la
am_test_mst_ibe_waters_OBJECTS = test_mst_ibe_waters.$(OBJEXT) \
	sim_mst_ibe.$(OBJEXT) waters_ibe.$(OBJEXT) \
	file_process.$(OBJEXT)
test_mst_ibe_waters_OBJECTS = $(am_test_mst_ibe_waters_OBJECTS)
test_mst_ibe_waters_LDADD = $(LDADD)
test_mst_ibe_waters_DEPENDENCIES = ../libpbc.la
am_test_ns_ibe_waters_OBJECTS = test_ns_ibe_waters.$(OBJEXT) \
	sim_ns_ibe.$(OBJEXT) waters_ibe.$(OBJEXT) \
	file_process.$(OBJEXT)
test_ns_ibe_waters_OBJECTS = $(am_test_ns_ibe_waters_OBJECTS)
test_ns_ibe_waters_LDADD = $(LDADD)
test_ns_ibe_waters_DEPENDENCIES = ../libpbc.la
am_test_ns_ibe_waters_addClient_OBJECTS =  \
	test_ns_ibe_waters_addClient.$(OBJEXT) sim_ns_ibe.$(OBJEXT) \
	waters_ibe.$(OBJEXT) file_process.$(OBJEXT)
test_ns_ibe_waters_addClient_OBJECTS =  \
	$(am_test_ns_ibe_waters_addClient_OBJECTS)
test_ns_ibe_waters_addClient_LDADD = $(LDADD)
test_ns_ibe_waters_addClient_DEPENDENCIES = ../libpbc.la
am_test_waters_multithreads_OBJECTS = waters_ibe.$(OBJEXT) \
	test_waters_threads_keyder.$(OBJEXT) file_process.$(OBJEXT)
test_waters_multithreads_OBJECTS =  \
	$(am_test_waters_multithreads_OBJECTS)
test_waters_multithreads_LDADD = $(LDADD)
test_waters_multithreads_DEPENDENCIES = ../libpbc.la
DEFAULT_INCLUDES = -I. -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
am__mv = mv -f
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=compile $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
SOURCES = $(test_mst_ibe_addClient_w_vf_SOURCES) \
	$(test_mst_ibe_addClient_wo_vf_SOURCES) \
	$(test_mst_ibe_waters_SOURCES) $(test_ns_ibe_waters_SOURCES) \
	$(test_ns_ibe_waters_addClient_SOURCES) \
	$(test_waters_multithreads_SOURCES)
DIST_SOURCES = $(test_mst_ibe_addClient_w_vf_SOURCES) \
	$(test_mst_ibe_addClient_wo_vf_SOURCES) \
	$(test_mst_ibe_waters_SOURCES) $(test_ns_ibe_waters_SOURCES) \
	$(test_ns_ibe_waters_addClient_SOURCES) \
	$(test_waters_multithreads_SOURCES)
ETAGS = etags
CTAGS = ctags
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
ACLOCAL = ${SHELL} /Users/yuanliang/Desktop/pbc-0.5.14/missing --run aclocal-1.11
ALLOCA = 
AMTAR = $${TAR-tar}
AR = ar
AS = as
AUTOCONF = ${SHELL} /Users/yuanliang/Desktop/pbc-0.5.14/missing --run autoconf
AUTOHEADER = ${SHELL} /Users/yuanliang/Desktop/pbc-0.5.14/missing --run autoheader
AUTOMAKE = ${SHELL} /Users/yuanliang/Desktop/pbc-0.5.14/missing --run automake-1.11
AWK = awk
CC = gcc
CCDEPMODE = depmode=gcc3
CFLAGS =  -Wall -W -Wfloat-equal -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wredundant-decls -Wendif-labels -Wshadow -pipe -ffast-math -U__STRICT_ANSI__ -std=gnu99 -fomit-frame-pointer -O3
CPP = gcc -E
CPPFLAGS = 
CYGPATH_W = echo
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DLLTOOL = false
DSYMUTIL = dsymutil
DUMPBIN = 
ECHO_C = \c
ECHO_N = 
ECHO_T = 
EGREP = /usr/bin/grep -E
EXEEXT = 
FGREP = /usr/bin/grep -F
GREP = /usr/bin/grep
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
LD = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ld
LDFLAGS = 
LEX = flex
LEXLIB = -ll
LEX_OUTPUT_ROOT = lex.yy
LIBOBJS = 
LIBPBC_DLL = 0
LIBPBC_LDFLAGS = 
LIBS = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIPO = lipo
LN_S = ln -s
LTLIBOBJS = 
MAKEINFO = ${SHELL} /Users/yuanliang/Desktop/pbc-0.5.14/missing --run makeinfo
MANIFEST_TOOL = :
MKDIR_P = .././install-sh -c -d
NM = /usr/bin/nm -B
NMEDIT = nmedit
OBJDUMP = objdump
OBJEXT = o
OTOOL = otool
OTOOL64 = :
PACKAGE = pbc
PACKAGE_BUGREPORT = blynn@cs.stanford.edu
PACKAGE_NAME = pbc
PACKAGE_STRING = pbc 0.5.14
PACKAGE_TARNAME = pbc
PACKAGE_URL = 
PACKAGE_VERSION = 0.5.14
PATH_SEPARATOR = :
PBC_LDFLAGS = 
RANLIB = ranlib
SED = /usr/bin/sed
SET_MAKE = 
SHELL = /bin/sh
STRIP = strip
VERSION = 0.5.14
YACC = bison -y
YFLAGS = 
abs_builddir = /Users/yuanliang/Desktop/pbc-0.5.14/example
abs_srcdir = /Users/yuanliang/Desktop/pbc-0.5.14/example
abs_top_builddir = /Users/yuanliang/Desktop/pbc-0.5.14
abs_top_srcdir = /Users/yuanliang/Desktop/pbc-0.5.14
ac_ct_AR = ar
ac_ct_CC = gcc
ac_ct_DUMPBIN = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = $${TAR-tar} chof - "$$tardir"
am__untar = $${TAR-tar} xf -
bindir = ${exec_prefix}/bin
build = arm-apple-darwin23.0.0
build_alias = 
build_cpu = arm
build_os = darwin23.0.0
build_vendor = apple
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = arm-apple-darwin23.0.0
host_alias = 
host_cpu = arm
host_os = darwin23.0.0
host_vendor = apple
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /Users/yuanliang/Desktop/pbc-0.5.14/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = $(top_builddir)/./install-sh -c -d
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr/local
program_transform_name = s,x,x,
psdir = ${docdir}
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target_alias = 
top_build_prefix = ../
top_builddir = ..
top_srcdir = ..
CLEANFILES = *~
AM_CPPFLAGS = -I../include
LDADD = ../libpbc.la -lgmp
test_waters_multithreads_SOURCES = waters_ibe.h waters_ibe.c test_waters_threads_keyder.c file_process.c
test_ns_ibe_waters_SOURCES = test_ns_ibe_waters.c sim_ns_ibe.c waters_ibe.h waters_ibe.c file_process.c
test_mst_ibe_waters_SOURCES = test_mst_ibe_waters.c  sim_mst_ibe.c waters_ibe.h waters_ibe.c  file_process.c
test_ns_ibe_waters_addClient_SOURCES = test_ns_ibe_waters_addClient.c sim_ns_ibe.c waters_ibe.h waters_ibe.c file_process.c
test_mst_ibe_addClient_wo_vf_SOURCES = test_mst_ibe_waters_addClient_wo_vf.c sim_mst_ibe.c waters_ibe.h waters_ibe.c file_process.c
test_mst_ibe_addClient_w_vf_SOURCES = test_mst_ibe_waters_addClient_w_vf.c sim_mst_ibe.c  waters_ibe.h waters_ibe.c file_process.c
test_waters_singlethread_SOURCES = waters_ibe.h waters_ibe.c test_waters_ibe.c file_process.c
test_waters_singlethread_c_SOURCES = waters_ibe.h waters_ibe.c test_waters_ibe_c.c file_process.c
all: all-am

.SUFFIXES:
.SUFFIXES: .c .lo .o .obj
$(srcdir)/Makefile.in:  $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --gnu example/Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --gnu example/Makefile
.PRECIOUS: Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure:  $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4):  $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(am__aclocal_m4_deps):

clean-noinstPROGRAMS:
	@list='$(noinst_PROGRAMS)'; test -n "$$list" || exit 0; \
	echo " rm -f" $$list; \
	rm -f $$list || exit $$?; \
	test -n "$(EXEEXT)" || exit 0; \
	list=`for p in $$list; do echo "$$p"; done | sed 's/$(EXEEXT)$$//'`; \
	echo " rm -f" $$list; \
	rm -f $$list
test_mst_ibe_addClient_w_vf$(EXEEXT): $(test_mst_ibe_addClient_w_vf_OBJECTS) $(test_mst_ibe_addClient_w_vf_DEPENDENCIES) $(EXTRA_test_mst_ibe_addClient_w_vf_DEPENDENCIES) 
	@rm -f test_mst_ibe_addClient_w_vf$(EXEEXT)
	$(LINK) $(test_mst_ibe_addClient_w_vf_OBJECTS) $(test_mst_ibe_addClient_w_vf_LDADD) $(LIBS)
test_mst_ibe_addClient_wo_vf$(EXEEXT): $(test_mst_ibe_addClient_wo_vf_OBJECTS) $(test_mst_ibe_addClient_wo_vf_DEPENDENCIES) $(EXTRA_test_mst_ibe_addClient_wo_vf_DEPENDENCIES) 
	@rm -f test_mst_ibe_addClient_wo_vf$(EXEEXT)
	$(LINK) $(test_mst_ibe_addClient_wo_vf_OBJECTS) $(test_mst_ibe_addClient_wo_vf_LDADD) $(LIBS)
test_mst_ibe_waters$(EXEEXT): $(test_mst_ibe_waters_OBJECTS) $(test_mst_ibe_waters_DEPENDENCIES) $(EXTRA_test_mst_ibe_waters_DEPENDENCIES) 
	@rm -f test_mst_ibe_waters$(EXEEXT)
	$(LINK) $(test_mst_ibe_waters_OBJECTS) $(test_mst_ibe_waters_LDADD) $(LIBS)
test_ns_ibe_waters$(EXEEXT): $(test_ns_ibe_waters_OBJECTS) $(test_ns_ibe_waters_DEPENDENCIES) $(EXTRA_test_ns_ibe_waters_DEPENDENCIES) 
	@rm -f test_ns_ibe_waters$(EXEEXT)
	$(LINK) $(test_ns_ibe_waters_OBJECTS) $(test_ns_ibe_waters_LDADD) $(LIBS)
test_ns_ibe_waters_addClient$(EXEEXT): $(test_ns_ibe_waters_addClient_OBJECTS) $(test_ns_ibe_waters_addClient_DEPENDENCIES) $(EXTRA_test_ns_ibe_waters_addClient_DEPENDENCIES) 
	@rm -f test_ns_ibe_waters_addClient$(EXEEXT)
	$(LINK) $(test_ns_ibe_waters_addClient_OBJECTS) $(test_ns_ibe_waters_addClient_LDADD) $(LIBS)
test_waters_multithreads$(EXEEXT): $(test_waters_multithreads_OBJECTS) $(test_waters_multithreads_DEPENDENCIES) $(EXTRA_test_waters_multithreads_DEPENDENCIES) 
	@rm -f test_waters_multithreads$(EXEEXT)
	$(LINK) $(test_waters_multithreads_OBJECTS) $(test_waters_multithreads_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/file_process.Po
include ./$(DEPDIR)/sim_mst_ibe.Po
include ./$(DEPDIR)/sim_ns_ibe.Po
include ./$(DEPDIR)/test_mst_ibe_waters.Po
include ./$(DEPDIR)/test_mst_ibe_waters_addClient_w_vf.Po
include ./$(DEPDIR)/test_mst_ibe_waters_addClient_wo_vf.Po
include ./$(DEPDIR)/test_ns_ibe_waters.Po
include ./$(DEPDIR)/test_ns_ibe_waters_addClient.Po
include ./$(DEPDIR)/test_waters_threads_keyder.Po
include ./$(DEPDIR)/waters_ibe.Po

.c.o:
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(COMPILE) -c $<

.c.obj:
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(COMPILE) -c `$(CYGPATH_W) '$<'`

.c.lo:
	$(LTCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Plo
#	source='$<' object='$@' libtool=yes \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(LTCOMPILE) -c -o $@ $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	mkid -fID $$unique
tags: TAGS

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	set x; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: CTAGS
CTAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags

distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile $(PROGRAMS)
installdirs:
install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	if test -z '$(STRIP)'; then \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	      install; \
	else \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	    "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'" install; \
	fi
mostlyclean-generic:

clean-generic:
	-test -z "$(CLEANFILES)" || rm -f $(CLEANFILES)

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic clean-libtool clean-noinstPROGRAMS \
	mostlyclean-am

distclean: distclean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags

dvi: dvi-am

dvi-am:

html: html-am

html-am:

info: info-am

info-am:

install-data-am:

install-dvi: install-dvi-am

install-dvi-am:

install-exec-am:

install-html: install-html-am

install-html-am:

install-info: install-info-am

install-info-am:

install-man:

install-pdf: install-pdf-am

install-pdf-am:

install-ps: install-ps-am

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic \
	maintainer-clean-local

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am:

.MAKE: install-am install-strip

.PHONY: CTAGS GTAGS all all-am check check-am clean clean-generic \
	clean-libtool clean-noinstPROGRAMS ctags distclean \
	distclean-compile distclean-generic distclean-libtool \
	distclean-tags distdir dvi dvi-am html html-am info info-am \
	install install-am install-data install-data-am install-dvi \
	install-dvi-am install-exec install-exec-am install-html \
	install-html-am install-info install-info-am install-man \
	install-pdf install-pdf-am install-ps install-ps-am \
	install-strip installcheck installcheck-am installdirs \
	maintainer-clean maintainer-clean-generic \
	maintainer-clean-local mostlyclean mostlyclean-compile \
	mostlyclean-generic mostlyclean-libtool pdf pdf-am ps ps-am \
	tags uninstall uninstall-am

maintainer-clean-local:
	-rm -rf Makefile.in

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
