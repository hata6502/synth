#CC := emcc
#PLATFORM_OPTIONS := -s WASM=1 -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=0 -s ASSERTIONS=2 \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' 

OPTIONS := -O3 -std=c++17 -I $(PWD) -I $(PWD)/cereal/include

all: synth

PHONY: clean
clean:
	-rm synth

synth: Makefile *.?pp core/*.?pp component/*.?pp command/*.?pp playdrv/*.?pp
	g++-7 $(OPTIONS) -o synth *.cpp core/*.cpp component/*.cpp command/*.cpp playdrv/*.cpp -luuid -lm
