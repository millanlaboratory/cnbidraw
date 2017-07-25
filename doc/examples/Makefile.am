AM_CXXFLAGS = -std=c++11 -I$(top_srcdir)/src

noinst_PROGRAMS = shapes images strings events

shapes_SOURCES = shapes.cpp
shapes_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

images_SOURCES = images.cpp
images_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

strings_SOURCES = strings.cpp
strings_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

events_SOURCES = events.cpp
events_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

