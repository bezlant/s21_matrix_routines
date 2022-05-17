CC=gcc
CFLAGS:=-c -Wall -Werror -Wextra -std=c11 $(ASAN)
ASAN=-g -fsanitize=address
#GCOV_FLAGS=-fprofile-arcs -ftest-coverage
#LIBS=-lcheck

TARGET=s21_matrix.a

OBJ_DIR=./objs

INC:=$(shell find -name "*.h")
SRC:=$(shell find -name "s21_*.c")

OBJS:=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

AR=ar rc
RAN=ranlib
RM=rm -f
MK=mkdir -p

obj: $(OBJS)

$(TARGET): $(OBJS)
	$(AR) $(TARGET) $(OBJS)
	$(RAN) $(TARGET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@$(MK) $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re open
