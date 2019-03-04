CC := g++
PLATFORM_OPTIONS :=

#CC := emcc
#PLATFORM_OPTIONS := -s WASM=1 -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=0 -s ASSERTIONS=2 \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' 

OPTIONS := -O3 -std=c++17 -I $(PWD) -I $(PWD)/cereal/include

all: synthcore

PHONY: clean
clean:
	-rm synthcore

synthcore: Makefile synthcore.cpp core/*.?pp com/*.?pp
	$(CC) $(OPTIONS) $(PLATFORM_OPTIONS) -o synthcore synthcore.cpp core/*.cpp com/*.cpp -luuid -lm
