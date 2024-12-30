NAME = philo
HEADER = ./includes/
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I $(HEADER) -pthread
OBJS = $(SRC:.c=.o)
SRC = ./src/main.c \
      ./src/error_and_stop.c \
      ./src/init.c \
      ./src/monitor.c \
      ./src/parser.c \
      ./src/routine.c \
      ./src/utils.c \
      ./src/time_utils.c \

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all