NAMEC := client
NAMES := server
BNAMEC := client_bonus
BNAMES := server_bonus
LIB := minitalk.h
CFILESC := ft_atoi.c client.c ft_memset.c
CFILESS :=  ft_atoi.c server.c ft_memset.c
OFILESC := $(CFILESC:%.c=%.o)
OFILESS := $(CFILESS:%.c=%.o)
CFLAGS := -Wall -Wextra -Werror
CC := cc
PRINTF := ft_printf/libftprintf.a
all: $(NAMES) $(NAMEC)
$(NAMES): $(OFILESS) 
	$(MAKE) -C ft_printf
	$(CC) $(OFILESS) $(PRINTF) -o server $(CFLAGS)
$(NAMEC): $(OFILESC)
	$(CC) $(OFILESC) $(PRINTF) -o client $(CFLAGS)

$(BNAMES): ft_atoi.o server_bonus.o ft_memset.o
	$(MAKE) -C ft_printf
	$(CC) ft_atoi.o server_bonus.o ft_memset.o $(PRINTF) -o server_bonus $(CFLAGS)
$(BNAMEC): ft_atoi.o client_bonus.o ft_memset.o
	$(CC) ft_atoi.o client_bonus.o ft_memset.o $(PRINTF) -o client_bonus $(CFLAGS)

%.o: %.c $(LIB)
	$(CC) -Wall -Wextra -Werror $< -c
clean:
	$(MAKE) -C ft_printf clean
	rm -rf $(OFILESS) $(OFILESC) ft_atoi.o client_bonus.o ft_memset.o server_bonus.o
fclean: clean
	$(MAKE) -C ft_printf fclean
	rm -rf  $(NAMES) $(NAMEC) $(BNAMES) $(BNAMEC)
re: fclean all

bonus: $(BNAMES) $(BNAMEC)

.PHONY:	clean fclean re all