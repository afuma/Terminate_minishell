
CC = cc
NAME = libftprintf.a

SRC = ft_printf.c \
	ft_utils_1.c \
	ft_utils_2.c \
	ft_dispatcher.c \
	ft_convert_1.c \
	ft_convert_2.c 

OBJ = $(SRC:.c=.o)

INCLUDES = ./ft_printf.h
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJ)
	ar crs $(NAME) $(OBJ)

.PHONY : all clean fclean re
