# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

# FLAGS will be passed to both the C and C++ compiler
FLAGS +=
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

FLAGS += \
	-Isrc/Common \
	-I$(RACK_DIR)/../MusicTools \
	-I$(RACK_DIR)/../MusicTools/Include \

# Add .cpp files to the build
SOURCES += \
	$(wildcard src/BitBus/*.cpp) \
	$(wildcard src/Common/*.cpp) \
	$(wildcard src/Morpher/*.cpp) \
	$(wildcard src/Tools/*.cpp) \
	$(RACK_DIR)/../MusicTools/AbstractEffect.cpp \
	$(RACK_DIR)/../MusicTools/AbstractOscilator.cpp \
	$(RACK_DIR)/../MusicTools/Maths.cpp \
	$(RACK_DIR)/../MusicTools/Note.cpp  


# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)
DISTRIBUTABLES += $(wildcard presets)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk
