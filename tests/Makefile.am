AM_CXXFLAGS = -std=c++11 -I$(top_srcdir)/src

check_PROGRAMS = test_engine test_shapes

test_engine_SOURCES = test_engine.cpp
test_engine_LDADD = -lcnbicore $(top_builddir)/src/libcnbidraw.la 

test_shapes_SOURCES = test_shapes.cpp
test_shapes_LDADD = -lcnbicore -ldrawtk $(top_builddir)/src/libcnbidraw.la 

TESTS = test_engine test_shapes


