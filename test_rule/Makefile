# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Directories
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRCS = $(SRC_DIR)/rule.c $(SRC_DIR)/card.c
# Test files
TESTS = $(SRC_DIR)/test_check_bluff.c $(SRC_DIR)/test_death_roulette.c $(SRC_DIR)/test_handle_challenge.c

# Output executables
TARGETS = $(BIN_DIR)/test_check_bluff $(BIN_DIR)/test_death_roulette $(BIN_DIR)/test_handle_challenge

# Create build and bin directories if they do not exist
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Default target
all: $(TARGETS)

# Compile each test file with the necessary source files
$(BIN_DIR)/test_check_bluff: $(SRC_DIR)/test_check_bluff.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/test_death_roulette: $(SRC_DIR)/test_death_roulette.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/test_handle_challenge: $(SRC_DIR)/test_handle_challenge.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean the build and bin directories
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGETS)

# Run all tests
run: $(TARGETS)
	@for test in $(TARGETS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

.PHONY: all clean run