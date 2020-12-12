# Compiler commands/flags
CC=g++
CC_FLAGS=-Wall -Wconversion -Werror -pedantic -std=c++17
CC_FLAGS_DEBUG=-g3
CC_FLAGS_RELEASE=-O3

# Source files
SRC_ROOT=./src
SRC_DIRS=$(wildcard $(SRC_ROOT)/*)
SRC_FILES=$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))

# Build output directories and targets
BUILD_ROOT=./build
DEBUG_DIR=$(BUILD_ROOT)/debug
RELEASE_DIR=$(BUILD_ROOT)/release
TARGETS=$(foreach dir,$(SRC_DIRS),$(notdir $(dir)))
DEBUG_TARGETS=$(addprefix $(DEBUG_DIR)/,$(TARGETS))
RELEASE_TARGETS=$(addprefix $(RELEASE_DIR)/,$(TARGETS))

# Object files and output directories
OBJ_DIR=objects
DEBUG_OBJ_DIR=$(addprefix $(DEBUG_DIR)/,$(OBJ_DIR))
RELEASE_OBJ_DIR=$(addprefix $(RELEASE_DIR)/,$(OBJ_DIR))
DEBUG_OBJ_DIRS=$(addprefix $(DEBUG_OBJ_DIR)/,$(TARGETS))
RELEASE_OBJ_DIRS=$(addprefix $(RELEASE_OBJ_DIR)/,$(TARGETS))
DEBUG_OBJ_FILES=$(foreach dir,$(SRC_DIRS),\
				$(DEBUG_OBJ_DIR)/$(notdir $(dir))/$(patsubst %.cpp,%.o,\
				$(notdir $(wildcard $(dir)/*.cpp))))
RELEASE_OBJ_FILES=$(foreach dir,$(SRC_DIRS),\
				  $(RELEASE_OBJ_DIR)/$(notdir $(dir))/$(patsubst %.cpp,%.o,\
				  $(notdir $(wildcard $(dir)/*.cpp))))

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
SRC_DIR=$(notdir $(@D))
SRC_FILE=$(SRC_ROOT)/$(SRC_DIR)/$(@F:.o=.cpp)

$(DEBUG_OBJ_FILES): $(SRC_FILE) | $$(@D)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_DEBUG) -c $(SRC_FILE) -o $@

$(RELEASE_OBJ_FILES): $(SRC_FILE) | $$(@D)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_RELEASE) -c $(SRC_FILE) -o $@

# Rules for compiling object files into executables
TARGET_NAME=$(notdir $@)
SOURCE_NAMES=$(patsubst %.cpp,%.o,\
			 $(notdir $(wildcard $(SRC_ROOT)/$(TARGET_NAME)/*.cpp)))
DEBUG_OBJS=$(addprefix $(DEBUG_OBJ_DIR)/$(TARGET_NAME)/,$(SOURCE_NAMES))
RELEASE_OBJS=$(addprefix $(RELEASE_OBJ_DIR)/$(TARGET_NAME)/,$(SOURCE_NAMES))

$(DEBUG_DIR)/%: $$(DEBUG_OBJS) | $(DEBUG_DIR)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_DEBUG) $(DEBUG_OBJS) -o $@

$(RELEASE_DIR)/%: $$(RELEASE_OBJS) | $(RELEASE_DIR)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_RELEASE) $(RELEASE_OBJS) -o $@
