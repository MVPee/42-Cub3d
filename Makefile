NAME = cub3D

LIBFT = srcs/libft
LIBMLX = ./MLX42/build/libmlx42.a 

OBJS_DIR = .objs
SRCS = 	main.c \
		srcs/cub3d/parsing/check_extension.c \
		srcs/cub3d/parsing/check_file.c \
		srcs/cub3d/parsing/check_map.c \
		srcs/cub3d/window_and_event/window.c \
		srcs/cub3d/window_and_event/event_hooks.c \
		srcs/cub3d/utils/utils.c \
		srcs/cub3d/parsing/map_optimization.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

CFLAGS = -I $(LIBFT) -g -ggdb3 -fsanitize=address #-Wall -Werror -Wextra
LDFLAGS = -lft -L $(LIBFT) -g -ggdb3 -fsanitize=address
LINUXFLAG = $(LIBMLX)-Iinclude -ldl -lglfw -pthread -lm

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT) 

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@gcc $(OBJS) $(LDFLAGS) $(LINUXFLAG) -o $(NAME)
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
