CC := clang
STD := -std=c17
WARN := -Wall -Wextra -Wpedantic -Werror
INCLUDES := -Iinclude

DEBUG_FLAGS := -g -O0 -DDEBUG -fsanitize=address,undefined
RELEASE_FLAGS := -O2 -DNDEBUG

TARGET := sentinel

SRC := $(wildcard src/*.c)

BUILD_DIR := build
DEBUG_DIR := $(BUILD_DIR)/debug
RELEASE_DIR := $(BUILD_DIR)/release

DEBUG_OBJ := $(patsubst src/%.c,$(DEBUG_DIR)/%.o,$(SRC))
RELEASE_OBJ := $(patsubst src/%.c,$(RELEASE_DIR)/%.o,$(SRC))

.PHONY: all debug release run clean

all: debug

debug: CFLAGS := $(STD) $(WARN) $(INCLUDES) $(DEBUG_FLAGS)
debug: $(DEBUG_DIR)/$(TARGET)

release: CFLAGS := $(STD) $(WARN) $(INCLUDES) $(RELEASE_FLAGS)
release: $(RELEASE_DIR)/$(TARGET)

$(DEBUG_DIR)/$(TARGET): $(DEBUG_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(RELEASE_DIR)/$(TARGET): $(RELEASE_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(DEBUG_DIR)/%.o: src/%.c | $(DEBUG_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(RELEASE_DIR)/%.o: src/%.c | $(RELEASE_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(DEBUG_DIR) $(RELEASE_DIR):
	mkdir -p $@

-include $(DEBUG_OBJ:.o=.d)
-include $(RELEASE_OBJ:.o=.d)

run: debug
	./$(DEBUG_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
