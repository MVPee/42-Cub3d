NAME = cub3D

LIBFT = srcs/libft

SRCS = 	main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -I $(LIBFT) -g #-Wall -Werror -Wextra #-ggdb3 -fsanitize=address
LDFLAGS = -lft -L $(LIBFT) -g #-ggdb3 -fsanitize=address

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT) 

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@gcc $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo   "${GREEN}./${NAME} ${RED}map${NC}"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	@rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re