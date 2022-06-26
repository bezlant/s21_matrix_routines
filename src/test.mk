CC=gcc
CFLAGS:=-Wall -Werror -Wextra -std=c11 -pedantic #-fanalyzer

ASAN=-g -fsanitize=address

INC:=$(shell find . -maxdepth 1 -name "*.h")
SRC:=$(shell find . -maxdepth 1 -name "s21*.c")
OBJS:=$(SRC:%.c=%.o)

# TESTS & COVERAGE
GCOV_FLAGS:=-fprofile-arcs -ftest-coverage $(ASAN)
TEST_LIBS:=$(shell pkg-config --cflags --libs check) 

TARGET_TEST=test
TARGET_TEST_LIB=s21_matrix_test.a
TEST_DIR=./tests

TEST_INC:=$(shell find $(TEST_DIR) -name "*.h")
TEST_SRC:=$(shell find $(TEST_DIR) -name "*.c")

TEST_OBJS:=$(TEST_SRC:%.c=%.o)

# GENERATE TEST.EXE FOR GCOV
all: $(TARGET_TEST) 

$(TARGET_TEST): CFLAGS+=$(GCOV_FLAGS)
$(TARGET_TEST): $(TEST_OBJS) $(TARGET_TEST_LIB)
	$(CC) $(CFLAGS) main.c -o $@ $^ $(TEST_LIBS) 
	./test
	
# GET ALL OBJS FROM TEST_DIR
$(TEST_OBJS): $(TEST_DIR)%.o:$(TEST_DIR)%.c $(TEST_INC) main.c
	$(CC) $(CFLAGS) -o $@ -c $<

# BUILD THE LIB AGAIN FOR TESTS
$(TARGET_TEST_LIB): $(OBJS) $(INC)
	ar rc $(TARGET_TEST_LIB) $(OBJS)
	ranlib $(TARGET_TEST_LIB)

# OBJS FOR LIB AGAIN

gcov: $(TARGET_TEST)
	gcov $(TEST_SRC) $(SRC)

coverage.info: gcov
	lcov --capture --directory . --output-file coverage.info

report: coverage.info
	genhtml coverage.info --output-directory coverage

open:
	open coverage/index.html

clean:
	rm -rf $(TEST_DIR)/*.gcno $(TEST_DIR)/*.gcda $(TEST_DIR)/*.o *.gcno *.gcda *.o coverag* *.gcov test.dSYM

fclean: clean
	rm -rf $(TARGET_TEST) $(TARGET_TEST_LIB)

re: fclean test

.PHONY: all clean fclean open
