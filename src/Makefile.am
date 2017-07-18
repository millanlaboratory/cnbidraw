AM_CXXFLAGS = -std=c++11 -I/usr/include/eigen3

lib_LTLIBRARIES = libcnbidraw.la

libcnbidraw_includedir = $(includedir)/cnbidraw
libcnbidraw_include_HEADERS = Engine.hpp \
							  Shape.hpp \
							  Window.hpp

libcnbidraw_la_SOURCES = Engine.hpp \
						 Engine.cpp \
						 Shape.hpp \
						 Shape.cpp \
						 Window.hpp \
						 Window.cpp 

libcnbidraw_la_LIBADD = -ldrawtk -lSDL -lcnbicore
libcnbidraw_la_LDFLAGS = $(AM_CFLAGS) \
						-version-info $(CURRENT):$(REVISION):$(AGE)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = cnbidraw.pc

