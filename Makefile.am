# Makefile.am for METIS

AM_CFLAGS = -O2
AM_CXXFLAGS = -O2
AM_YFLAGS = -d

lib_LIBRARIES = libmetis.a

libmetis_a_SOURCES = \
	parse.yy \
	lex.ll \
	data.h \
	parser.h \
	charref.cpp \
	stringdata.cpp sd-utf8code.cpp \
	metis_base.cpp \
	metis_celm.cpp \
	ctext.cpp \
	cattr.cpp \
	strescape.h strescape.cpp \
	strvisitor.h strvisitor.cpp


metisincludedir = @includedir@/metis
metisinclude_HEADERS = \
	data.h \
	parser.h \
	strvisitor.h \
	strescape.h


CLEANFILES = *~

#eof
