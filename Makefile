#################
# Configuration #
#################

MAIN_ROOT=main
SRC_ROOT=src
TEST_ROOT=test
ROOT_NAMES=$(MAIN_ROOT) $(SRC_ROOT) $(TEST_ROOT)
BUILD_ROOT=build
OBJ_DIR_NAME=objects
DEBUG=debug
RELEASE=release
CONFIGS=$(DEBUG) $(RELEASE)
TEST_TARGET_NAME=test
TARGET_NAMES=$(foreach dir,$(wildcard $(MAIN_ROOT)/*),$(notdir $(dir)))

#############
# Functions #
#############

# build_dir(config)
build_dir=$(BUILD_ROOT)/$(1)

# obj_dir(config)
obj_dir=$(call build_dir,$(1))/$(OBJ_DIR_NAME)

# object(config, cpp_source)
object=$(call obj_dir,$(1))/$(2:.cpp=.o)

# object_all_configs(cpp_source)
object_all_configs=$(foreach config,$(CONFIGS),$(call object,$(config),$(1)))

# targets(config)
targets=$(addprefix $(call build_dir,$(1))/,$(TARGET_NAMES))

# test_target(config)
test_target=$(call build_dir,$(1))/$(TEST_TARGET_NAME)

# obj_dirs(config, root_dir)
obj_dirs=$(foreach dir,$(wildcard $(2)/*),$(call obj_dir,$(1))/$(dir))

# obj_files(config, root_dir)
obj_files=$(addprefix $(call obj_dir,$(1))/,\
		  $(patsubst %.cpp,%.o,\
		  $(wildcard $(addsuffix /*.cpp,$(wildcard $(2)/*)))))

# obj_files_all_roots(config)
obj_files_all_roots=$(foreach root,$(ROOT_NAMES),\
					$(call obj_files,$(1),$(root)))

ALL_BUILD_DIRS=$(foreach config,$(CONFIGS),$(call build_dir,$(config)))
ALL_OBJ_DIRS=$(foreach config,$(CONFIGS),\
			 $(foreach root,$(ROOT_NAMES),\
			 $(call obj_dirs,$(config),$(root))))
ALL_OBJ_FILES=$(foreach config,$(CONFIGS),\
			  $(call obj_files_all_roots,$(config)))

##################
# Commands/Flags #
##################

CC=g++
CC_FLAGS=-Wall -Wconversion -Werror -pedantic -std=c++17 -MMD\
		 -iquote $(SRC_ROOT)
CC_FLAGS_DEBUG=-g3
CC_FLAGS_RELEASE=-O3

#############
# Generated #
#############

GENERATED_HEADER_DEPENDENCIES=$(ALL_OBJ_FILES:.o=.d)
-include $(GENERATED_HEADER_DEPENDENCIES)

#########
# Rules #
#########

.DEFAULT_GOAL:=debug

.PHONY: all
all: debug release tests

.PHONY: debug
debug: $(call targets,$(DEBUG))

.PHONY: release
release: $(call targets,$(RELEASE))

.PHONY: tests
tests: $(call test_target,$(DEBUG))

.PHONY: clean
clean:
	rm -rf $(BUILD_ROOT)

$(ALL_BUILD_DIRS) $(ALL_OBJ_DIRS):
	mkdir -p $@

# Secondary expansion section. Add rules that should not use this above this
# point.
.SECONDEXPANSION:

# Rules for compiling source files into object files

# src_file(config)
src_file=$(patsubst $(call obj_dir,$(1))/%.o,%.cpp,$@)

$(call obj_files_all_roots,$(DEBUG)): $$(call src_file,$(DEBUG)) | $$(@D)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_DEBUG) -c $(call src_file,$(DEBUG)) -o $@

$(call obj_files_all_roots,$(RELEASE)): $$(call src_file,$(RELEASE)) | $$(@D)
	$(CC) $(CC_FLAGS) $(CC_FLAGS_RELEASE) -c $(call src_file,$(RELEASE)) -o $@

# Rules for compiling object files into executables
TARGET_NAME=$(notdir $@)

SOURCE_NAMES=$(patsubst %.cpp,%.o,\
			 $(notdir $(wildcard $(MAIN_ROOT)/$(TARGET_NAME)/*.cpp)))

# main_objs(config)
main_objs=$(addprefix $(call obj_dir,$(1))/$(MAIN_ROOT)/$(TARGET_NAME)/,\
		   $(SOURCE_NAMES)) $(call obj_files,$(1),$(SRC_ROOT))

# test_objs(config)
test_objs=$(call obj_files,$(1),$(TEST_ROOT))\
		  $(call obj_files,$(1),$(SRC_ROOT))

$(call targets,$(DEBUG)): $$(call main_objs,$(DEBUG)) |\
	$(call build_dir,$(DEBUG))
	$(CC) $(CC_FLAGS) $(CC_FLAGS_DEBUG) $(call main_objs,$(DEBUG)) -o $@

$(call targets,$(RELEASE)): $$(call main_objs,$(RELEASE)) |\
	$(call build_dir,$(RELEASE))
	$(CC) $(CC_FLAGS) $(CC_FLAGS_RELEASE) $(call main_objs,$(RELEASE)) -o $@

$(call test_target,$(DEBUG)): $$(call test_objs,$(DEBUG)) |\
	$(call build_dir,$(DEBUG))
	$(CC) $(CC_FLAGS) $(CC_FLAGS_DEBUG) $(call test_objs,$(DEBUG)) -o $@
