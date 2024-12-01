# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Directories
SRC_DIR = ..  # Parent directory where rule.c, card.c, and game.c are located
BIN_DIR = bin

# Source files
SRCS = $(SRC_DIR)/rule.c $(SRC_DIR)/card.c $(SRC_DIR)/game.c
# Test files
TESTS = test_check_bluff.c test_death_roulette.c test_handle_challenge.c

# Output executables
TARGETS = $(BIN_DIR)/test_check_bluff $(BIN_DIR)/test_death_roulette $(BIN_DIR)/test_handle_challenge

# Create bin directory if it does not exist
$(shell mkdir -p $(BIN_DIR))

# Default target
all: $(TARGETS)

# Compile each test file with the necessary source files
$(BIN_DIR)/test_check_bluff: test_check_bluff.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ $< $(SRCS)

$(BIN_DIR)/test_death_roulette: test_death_roulette.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ $< $(SRCS)

$(BIN_DIR)/test_handle_challenge: test_handle_challenge.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ $< $(SRCS)

# Clean the bin directory
clean:
	rm -rf $(BIN_DIR)/*

# Run all tests
run: $(TARGETS)
	@for test in $(TARGETS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

.PHONY: all clean run