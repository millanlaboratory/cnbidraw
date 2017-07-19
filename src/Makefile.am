AM_CXXFLAGS = -std=c++11 -I/usr/include/eigen3

lib_LTLIBRARIES = libcnbidraw.la

libcnbidraw_includedir = $(includedir)/cnbidraw
libcnbidraw_include_HEADERS = Flags.hpp \
							  Engine.hpp \
							  Window.hpp \
							  Shape.hpp \
						 	  Arrow.hpp \
						 	  Circle.hpp \
						 	  CircleStrip.hpp \
						 	  Cross.hpp \
						 	  Rectangle.hpp

libcnbidraw_la_SOURCES = Flags.hpp \
						 Engine.hpp \
						 Engine.cpp \
						 Window.hpp \
						 Window.cpp \
						 Shape.hpp \
						 Shape.cpp \
						 Arrow.hpp \
						 Arrow.cpp \
						 Circle.hpp \
						 Circle.cpp \
						 CircleStrip.hpp \
						 CircleStrip.cpp \
						 Cross.hpp \
						 Cross.cpp \
						 Rectangle.hpp \
						 Rectangle.cpp 

libcnbidraw_la_LIBADD = -ldrawtk -lSDL -lcnbicore
libcnbidraw_la_LDFLAGS = $(AM_CFLAGS) \
						-version-info $(CURRENT):$(REVISION):$(AGE)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = cnbidraw.pc

