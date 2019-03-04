OPTIONS := -s WASM=1 -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=0 -s ASSERTIONS=2 \
		-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
		-O3 -std=c++17 -Wno-exceptions \
		-I $(PWD) -I $(PWD)/cereal/include

all: ../html/module.js

PHONY: clean
clean:
	-rm ../html/module.*
	-rm core/core.o
	-rm com/com.o

../html/module.js: Makefile module.cpp core/core.o com/com.o
	emcc $(OPTIONS) -o ../html/module.js module.cpp core/core.o com/com.o

core/core.o: Makefile core/*.?pp
	emcc $(OPTIONS) -o core/core.o core/*.cpp

com/com.o: Makefile com/*.?pp
	emcc $(OPTIONS) -o com/com.o com/*.cpp
