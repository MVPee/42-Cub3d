NAME = cub3D

LIBFT = srcs/libft
LIBMLX = ./MLX42/build/libmlx42.a 

OBJS_DIR = .objs
SRCS = 	main.c \
		srcs/cub3d/init_and_unit/init_and_unit.c \
		srcs/cub3d/parsing/check_file.c \
		srcs/cub3d/parsing/check_map.c \
		srcs/cub3d/window_and_event/window.c \
		srcs/cub3d/window_and_event/event_hooks.c \
		srcs/cub3d/utils/utils.c \
		srcs/cub3d/rendering/raycasting/raycasting.c \
		srcs/cub3d/rendering/raycasting/raycasting_utils.c \
		srcs/cub3d/rendering/minimap/minimap.c \
		srcs/cub3d/rendering/minimap/minimap_utils.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))


OS = $(shell uname)
FLAG_OPTI = -Ofast -ffast-math -O3
FLAG = $(LIBMLX) -Iinclude
ifeq ($(OS), Darwin)
    PROJECT_FLAGS = -L "/Users/$(USER)/.brew/opt/glfw/lib/" -lglfw -lm -framework Cocoa -framework OpenGL -framework IOKit $(FLAG_OPTI)
else ifeq($(OS), Darwin)
    PROJECT_FLAGS = -lglfw -lm -lGL $(FLAG_OPTI)
else
    $(error "Unsupported OS")
endif

CFLAGS = -I $(LIBFT) -Wall -Werror -Wextra -g -ggdb3 -fsanitize=address 
LDFLAGS = -lft -L $(LIBFT) -Wall -Werror -Wextra -g -ggdb3 -fsanitize=address
FLAG = $(LIBMLX) -Iinclude
LINUXFLAG2 = -lglfw -lm -lGL $(FLAG_OPTI)
MACOSFLAG = -L "/Users/$(USER)/.brew/opt/glfw/lib/" -lglfw -lm -O3 -Ofast -ffast-math -framework Cocoa -framework OpenGL -framework IOKit $(FLAG_OPTI)
FLAG_OPTI = -Ofast -ffast-math -O3

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@gcc $(OBJS) $(LDFLAGS) $(FLAG) $(PROJECT_FLAGS) -o $(NAME)
	@echo   "${GREEN}./${NAME} ${RED}map${NC}"

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@gcc $(CFLAGS) $(FLAG_OPTI) $ -c $< -o $@

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
