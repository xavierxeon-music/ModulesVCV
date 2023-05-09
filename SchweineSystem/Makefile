# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../Rack

# FLAGS will be passed to both the C and C++ compiler
FLAGS += 
CFLAGS += 
CXXFLAGS += -D NON_DAISY_DEVICE 

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

FLAGS += \
	-Isrc/_Base \
	-Isrc/_Gui \
	-Isrc/_MusicTools \
	-Isrc/_MusicTools/Include \
	-Isrc/_MusicTools/Memory \
	-Isrc/_MusicTools/RememberDummy \


# Add .cpp files to the build
SOURCES += \
	$(wildcard src/_Base/*.cpp) \
	$(wildcard src/_Gui/*.cpp) \
	$(wildcard src/_MusicTools/*.cpp) \
	$(wildcard src/_MusicTools/Memory/*.cpp) \
	$(wildcard src/BitBus/*.cpp) \
	$(wildcard src/Effects/*.cpp) \
	$(wildcard src/Hardware/*.cpp) \
	$(wildcard src/Morpher/*.cpp) \
	$(wildcard src/Midi/*.cpp) \
	$(wildcard src/Sequencer/*.cpp) \
	$(wildcard src/Synths/*.cpp) \
	$(wildcard src/Utilities/*.cpp) \


# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)
DISTRIBUTABLES += $(wildcard presets)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

