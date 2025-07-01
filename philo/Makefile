NAME = philo

SRC_FILES = validation.c main.c

SRCS = $(addprefix ./philo/, $(SRC_FILES))

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror


all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS)  -c -o $@ $<

clean :
	rm -f $(OBJS)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
