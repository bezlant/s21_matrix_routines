CC=gcc
CFLAGS:=-Wall -Werror -Wextra -std=c11 
ASAN=-g #-fsanitize=address

TARGET=s21_matrix.a

INC:=$(shell find . -maxdepth 1 -name "*.h")
SRC:=$(shell find . -maxdepth 1 -name "s21*.c")
OBJS:=$(SRC:%.c=%.o)

# s21_matrix.a
all: $(TARGET)

$(TARGET): $(OBJS)
	ar -vrcs $(TARGET) $(OBJS)
	ranlib $(TARGET)

$(OBJS): %.o:%.c $(SRC) $(INC)
	$(CC) $(CFLAGS) -o $@ -c $< $(ASAN)

test:
	$(MAKE) -f test.mk

report:
	$(MAKE) -f test.mk report

open:
	$(MAKE) -f test.mk open

clean:
	rm -rf $(OBJS)  

fclean: clean
	rm -rf $(TARGET)
	$(MAKE) -f test.mk fclean


.PHONY: all clean fclean open
