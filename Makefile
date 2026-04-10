# Define your compiler and flags
CC = gcc
CFLAGS = -Isrc -Isrc/helpers -Isrc/benchmark -Isrc/algorithms -Isrc/tests -Wall

# Use wildcards to grab everything
SRCS = 	src/main.c \
		src/helpers/*.c \
		src/benchmark/*.c \
		src/algorithms/*.c \
		src/tests/test_sorted.c \
		src/tests/test_shuffle.c

SRCS_TEST = src/tests/test_shuffle.c \
			src/tests/test_sorted.c \
			src/helpers/array_gen.c \
			src/tests/validation.c \

# The "all" target - This is what runs when you just type 'make'
all:
	$(CC) $(CFLAGS) $(SRCS) -o main_app

# A target for your tests
test_shuffle:
	$(CC) $(CFLAGS) $(SRCS_TEST) -o test_shuffle_bin

# Clean target - To remove the executables and start fresh
clean:
	rm -f main_app test_shuffle_bin