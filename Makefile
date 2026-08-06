CC := clang
STD := -std=c17
WARN := -Wall -Wextra -Wpedantic -Werror
INCLUDES := -Iinclude

DEBUG_FLAGS := -g -O0 -DDEBUG -fsanitize=address,undefined
RELEASE_FLAGS := -O2 -DNDEBUG

TARGET := sentinel

ifeq ($(OS),Windows_NT)
    EXE := .exe
    MKDIR = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
    RMDIR = if exist "$(subst /,\,$1)" rmdir /s /q "$(subst /,\,$1)"
else
    EXE :=
    MKDIR = mkdir -p $1
    RMDIR = rm -rf $1
endif

SRC := $(wildcard src/*.c)

BUILD_DIR := build
DEBUG_DIR := $(BUILD_DIR)/debug
RELEASE_DIR := $(BUILD_DIR)/release

DEBUG_OBJ := $(patsubst src/%.c,$(DEBUG_DIR)/%.o,$(SRC))
RELEASE_OBJ := $(patsubst src/%.c,$(RELEASE_DIR)/%.o,$(SRC))

.PHONY: all debug release run clean

all: debug

debug: CFLAGS := $(STD) $(WARN) $(INCLUDES) $(DEBUG_FLAGS)
debug: $(DEBUG_DIR)/$(TARGET)$(EXE)

release: CFLAGS := $(STD) $(WARN) $(INCLUDES) $(RELEASE_FLAGS)
release: $(RELEASE_DIR)/$(TARGET)$(EXE)

$(DEBUG_DIR)/$(TARGET)$(EXE): $(DEBUG_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(RELEASE_DIR)/$(TARGET)$(EXE): $(RELEASE_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(DEBUG_DIR)/%.o: src/%.c | $(DEBUG_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(RELEASE_DIR)/%.o: src/%.c | $(RELEASE_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(DEBUG_DIR) $(RELEASE_DIR):
	$(call MKDIR,$@)

-include $(DEBUG_OBJ:.o=.d)
-include $(RELEASE_OBJ:.o=.d)

run: debug
	$(DEBUG_DIR)/$(TARGET)$(EXE)

clean:
	$(call RMDIR,$(BUILD_DIR))
