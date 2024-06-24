# Define the compiler
CC = gcc

# Define the source files and corresponding executables
SRCS = $(wildcard $(SUBDIR)/p*.c)
EXES = $(patsubst %.c,$(SUBDIR)/bin/%,$(notdir $(SRCS)))

# Default target to build all executables
all: $(EXES)

# Rule to build each executable
$(SUBDIR)/bin/%: $(SUBDIR)/%.c | $(SUBDIR)/bin
	$(CC) -o $@ $<

# Create the bin directory if it doesn't exist
$(SUBDIR)/bin:
	mkdir -p $(SUBDIR)/bin

# Clean up the bin directory
clean:
	rm -rf $(SUBDIR)/bin

# Phony targets
.PHONY: all clean

