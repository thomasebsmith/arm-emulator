# Source files
MAIN_ROOT=main
MAIN_DIRS=$(wildcard $(MAIN_ROOT)/*)
SRC_ROOT=src
SRC_DIRS=$(wildcard $(SRC_ROOT)/*)

# Build output directories and targets
BUILD_ROOT=build
DEBUG_DIR=$(BUILD_ROOT)/debug
RELEASE_DIR=$(BUILD_ROOT)/release
TARGETS=$(foreach dir,$(MAIN_DIRS),$(notdir $(dir)))
DEBUG_TARGETS=$(addprefix $(DEBUG_DIR)/,$(TARGETS))
RELEASE_TARGETS=$(addprefix $(RELEASE_DIR)/,$(TARGETS))

# Object files and output directories
OBJ_DIR=objects
DEBUG_OBJ_DIR=$(addprefix $(DEBUG_DIR)/,$(OBJ_DIR))
RELEASE_OBJ_DIR=$(addprefix $(RELEASE_DIR)/,$(OBJ_DIR))
DEBUG_OBJ_DIRS=$(foreach dir,$(SRC_DIRS) $(MAIN_DIRS),$(DEBUG_OBJ_DIR)/$(dir))
RELEASE_OBJ_DIRS=$(foreach dir,$(SRC_DIRS) $(MAIN_DIRS),$(RELEASE_OBJ_DIR)/$(dir))

DEBUG_SRC_OBJ_FILES=$(foreach dir,$(SRC_DIRS),\
					$(DEBUG_OBJ_DIR)/$(dir)/$(patsubst \
					%.cpp,%.o,$(notdir $(wildcard $(dir)/*.cpp))))
DEBUG_MAIN_OBJ_FILES=$(foreach dir,$(MAIN_DIRS),\
				$(DEBUG_OBJ_DIR)/$(dir)/$(patsubst \
				%.cpp,%.o,$(notdir $(wildcard $(dir)/*.cpp))))
DEBUG_OBJ_FILES=$(DEBUG_SRC_OBJ_FILES) $(DEBUG_MAIN_OBJ_FILES)

RELEASE_SRC_OBJ_FILES=$(foreach dir,$(SRC_DIRS),\
					$(RELEASE_OBJ_DIR)/$(dir)/$(patsubst \
					%.cpp,%.o,$(notdir $(wildcard $(dir)/*.cpp))))
RELEASE_MAIN_OBJ_FILES=$(foreach dir,$(MAIN_DIRS),\
				$(RELEASE_OBJ_DIR)/$(dir)/$(patsubst \
				%.cpp,%.o,$(notdir $(wildcard $(dir)/*.cpp))))
RELEASE_OBJ_FILES=$(RELEASE_SRC_OBJ_FILES) $(RELEASE_MAIN_OBJ_FILES)

# Compiler commands/flags
CC=g++
CC_FLAGS=-Wall -Wconversion -Werror -pedantic -std=c++17 -iquote $(SRC_ROOT)
CC_FLAGS_DEBUG=-g3
CC_FLAGS_RELEASE=-O3

# Rules
.DEFAULT: debug

.PHONY: all
all: debug release

.PHONY: debug
debug: $(DEBUG_TARGETS)

.PHONY: release
release: $(RELEASE_TARGETS)

.PHONY: clean
clean:
	rm -rf $(BUILD_ROOT)

$(DEBUG_DIR) $(RELEASE_DIR) $(DEBUG_OBJ_DIRS) $(RELEASE_OBJ_DIRS):
	mkdir -p $@

# Secondary expansion section. Add rules that should not use this above this
# point.
.SECONDEXPANSION:

# Rules for compiling source files into object files
SRC_FILE_DEBUG=$(patsubst $(DEBUG_OBJ_DIR)/%.o,%.cpp,$@)
SRC_FILE_RELEASE=$(patsubst $(RELEASE_OBJ_DIR)/%.o,%.cpp,$@)

$(DEBUG_OBJ_FILES): $$(SRC_FILE_DEBUG) | $$(@D)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_DEBUG) -c $(SRC_FILE_DEBUG) -o $@

$(RELEASE_OBJ_FILES): $$(SRC_FILE_RELEASE) | $$(@D)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_RELEASE) -c $(SRC_FILE_RELEASE) -o $@

# Rules for compiling object files into executables
TARGET_NAME=$(notdir $@)
SOURCE_NAMES=$(patsubst %.cpp,%.o,\
			 $(notdir $(wildcard $(MAIN_ROOT)/$(TARGET_NAME)/*.cpp)))
DEBUG_OBJS=$(addprefix $(DEBUG_OBJ_DIR)/$(MAIN_ROOT)/$(TARGET_NAME)/,\
		   $(SOURCE_NAMES)) $(DEBUG_SRC_OBJ_FILES)
RELEASE_OBJS=$(addprefix $(RELEASE_OBJ_DIR)/$(MAIN_ROOT)/$(TARGET_NAME)/,\
			 $(SOURCE_NAMES)) $(RELEASE_SRC_OBJ_FILES)

$(DEBUG_DIR)/%: $$(DEBUG_OBJS) | $(DEBUG_DIR)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_DEBUG) $(DEBUG_OBJS) -o $@

$(RELEASE_DIR)/%: $$(RELEASE_OBJS) | $(RELEASE_DIR)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_RELEASE) $(RELEASE_OBJS) -o $@
