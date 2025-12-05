# === Compiler settings ===
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# === Source code files ===
SRCS = \
	src/main.c \
	src/hanoi_iterative.c \
	src/hanoi_recursive.c \
	src/utils.c

OBJS   = $(SRCS:.c=.o)
TARGET = hanoi

# === Default: build everything ===
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# === Run the program ===
run: $(TARGET)
	./$(TARGET)

# === Clean compiled files ===
clean:
	rm -f $(OBJS) $(TARGET)