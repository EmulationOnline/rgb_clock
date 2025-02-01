all: rgb_clock

.PHONY: deps
deps:
	# mac deps
	brew install pkg-config
	brew install sdl2

rgb_clock: rgb_clock.cc deps
	$(CXX) `pkg-config --libs --cflags sdl2` rgb_clock.cc -o rgb_clock
