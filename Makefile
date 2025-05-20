CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = ./src
DS_SRC_DIR = $(SRC_DIR)/ds
TESTS_DIR = ./tests
BIN_DIR = ./bin
DS_OBJS = $(patsubst $(DS_SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(wildcard $(DS_SRC_DIR)/*.c))
TEST_SRC = $(wildcard $(TESTS_DIR)/heapq_test_i.c)
TEST_EXEC = $(BIN_DIR)/tests

# Create directories if they don't exist
prepare:
	@mkdir -p $(BIN_DIR)

# Compile data structures source files
$(BIN_DIR)/%.o: $(DS_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile tests source files and link with data structures object files
$(TEST_EXEC): $(TEST_SRC) $(DS_OBJS)
	$(CC) $(CFLAGS) -I $(DS_SRC_DIR) $^ -o $@

# Compile all
all: prepare $(DS_OBJS) $(TEST_EXEC)

# Run the tests
run: $(TEST_EXEC)
	@./$(TEST_EXEC)

# Clean object files and executables
clean:
	@rm -f $(BIN_DIR)/*.o $(TEST_EXEC)

.PHONY: all prepare run clean