NAME := libftprintf.a
LIB := ft_printf.h
CFILES := ft_printf.c ft_printf_utils.c ft_oxhex.c ft_putnbr_fd.c
COBJECTS := $(CFILES:%.c=%.o)
CFLAGS := -Wall -Wextra -Werror -c
CC = cc

all: $(NAME)

$(NAME): $(COBJECTS)
	ar rcs $@ $?

%.o: %.c $(LIB)
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(COBJECTS)
fclean: clean
	rm -rf $(NAME)
re: fclean all