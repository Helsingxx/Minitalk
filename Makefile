NAMES := server
NAMEC := client

BNAMES := server_bonus
BNAMEC := client_bonus

LIB := minitalk.h minitalk_bonus.h ft_printf/ft_printf.h
PRINTF := ft_printf/libftprintf.a

CFILESS := server.c
CFILESC := tools.c client.c
OFILESS := $(CFILESS:%.c=%.o)
OFILESC := $(CFILESC:%.c=%.o)

BS :=  server_bonus.c
BC := tools_bonus.c client_bonus.c
OBS := $(BS:%.c=%.o)
OBC := $(BC:%.c=%.o)


ADDITIONAL := ft_atoi.c ft_isint.c
ADDO := $(ADDITIONAL:%.c=%.o)
CC := cc
CFLAGS := -Wall -Wextra -Werror

all: $(NAMES) $(NAMEC)

$(NAMES): $(OFILESS) $(ADDO)
	$(MAKE) -C ft_printf
	$(CC) $^ $(PRINTF) -o $@ $(CFLAGS)

$(NAMEC): $(OFILESC) $(ADDO)
	$(MAKE) -C ft_printf
	$(CC) $^ $(PRINTF) -o $@ $(CFLAGS)

$(BNAMES): $(OBS) $(ADDO)
	$(MAKE) -C ft_printf
	$(CC) $^ $(PRINTF) -o $@ $(CFLAGS)

$(BNAMEC): $(OBC) $(ADDO)
	$(CC) $^ $(PRINTF) -o $@ $(CFLAGS)

%.o: %.c $(LIB)
	$(CC) $< -c $(CFLAGS)

clean:
	$(MAKE) -C ft_printf clean
	rm -rf $(OFILESS) $(OFILESC) $(OBS) $(OBC) $(ADDO)

fclean: clean
	$(MAKE) -C ft_printf fclean
	rm -rf $(NAMES) $(NAMEC) $(BNAMES) $(BNAMEC)

re: fclean all

bonus: $(BNAMES) $(BNAMEC)

.PHONY:	clean fclean re all bonus