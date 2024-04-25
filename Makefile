NAME = cub3D

LIBFT = srcs/libft

OBJS_DIR = .objs
SRCS = 	main.c \
		srcs/cub3d/parsing/check_extension.c \
		srcs/cub3d/parsing/check_map.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

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

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@gcc $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(dir $(OBJS))

clean:
	$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) maps/cub.cub

.PHONY: all clean fclean re run
