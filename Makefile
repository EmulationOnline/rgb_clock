all: rgb_clock

.PHONY: macdeps debdeps

macdeps:
	# mac deps
	brew install pkg-config
	brew install sdl2

debdeps:
	# debian/ubuntu deps
	sudo apt install libsdl2-dev pkg-config
	

rgb_clock: rgb_clock.cc 
	$(CXX) `pkg-config --libs --cflags sdl2` rgb_clock.cc -o rgb_clock
