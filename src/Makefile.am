AM_CXXFLAGS = -std=c++11 -I/usr/include/eigen3

lib_LTLIBRARIES = libcnbidraw.la

libcnbidraw_includedir = $(includedir)/cnbidraw
libcnbidraw_include_HEADERS = Flags.hpp \
							  Engine.hpp \
							  Window.hpp \
							  EventsEngine.hpp \
							  EventsHandler.hpp \
							  Shape.hpp \
							  ShapeMap.hpp \
						 	  Arrow.hpp \
						 	  Circle.hpp \
						 	  CircleStrip.hpp \
						 	  Cross.hpp \
						 	  Rectangle.hpp \
							  Image.hpp \
							  String.hpp

libcnbidraw_la_SOURCES = Flags.hpp \
						 Engine.hpp \
						 Engine.cpp \
						 Window.hpp \
						 Window.cpp \
						 EventsEngine.hpp \
						 EventsEngine.cpp \
						 EventsHandler.hpp \
						 EventsHandler.cpp \
						 Shape.hpp \
						 Shape.cpp \
						 ShapeMap.hpp \
						 ShapeMap.cpp \
						 Arrow.hpp \
						 Arrow.cpp \
						 Circle.hpp \
						 Circle.cpp \
						 CircleStrip.hpp \
						 CircleStrip.cpp \
						 Cross.hpp \
						 Cross.cpp \
						 Rectangle.hpp \
						 Rectangle.cpp \
						 Image.hpp \
						 Image.cpp \
						 String.hpp \
						 String.cpp

libcnbidraw_la_LIBADD = -ldrawtk -lSDL -lcnbicore
libcnbidraw_la_LDFLAGS = $(AM_CFLAGS) \
						-version-info $(CURRENT):$(REVISION):$(AGE)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = cnbidraw.pc

