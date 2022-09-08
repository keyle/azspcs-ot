COMPILER = clang
SOURCE_LIBS = -Ilib/ -Llib/
INCLUDES = -include **.h # NOTE not used below as it compiles the *.h files as well and generates multiple outputs
OSX_OPT = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
WARNINGS = -Wall
OSX_OUT = -o "testing"
DEBUG_BUILD = -ggdb -v
CFILES = main.c

build_osx:
	$(COMPILER) $(CFILES) $(OSX_OUT) $(WARNINGS)
	./testing

runner:
	$(COMPILER) $(CFILES) -ffast-math -O2 -o "release"

