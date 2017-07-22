AM_CXXFLAGS = -std=c++11 -I$(top_srcdir)/src

check_PROGRAMS = test_engine test_shapes test_images test_strings test_events

test_engine_SOURCES = test_engine.cpp
test_engine_LDADD = -lcnbicore $(top_builddir)/src/libcnbidraw.la 

test_shapes_SOURCES = test_shapes.cpp
test_shapes_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

test_images_SOURCES = test_images.cpp
test_images_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

test_strings_SOURCES = test_strings.cpp
test_strings_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

test_events_SOURCES = test_events.cpp
test_events_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

TESTS = test_engine test_shapes test_images test_strings test_events


