NAME = cub3D

LIBFT = libft
LIBMLX = MLX42/build/libmlx42.a

OBJS_DIR = .objs

SRCS = 	main.c \
		srcs/init_and_unit/init_and_unit.c \
		srcs/init_and_unit/init_and_unit2.c \
		srcs/parsing/check_file.c \
		srcs/parsing/check_map.c \
		srcs/window_and_event/window.c \
		srcs/window_and_event/event_hooks.c \
		srcs/utils/utils.c \
		srcs/utils/utils2.c \
		srcs/rendering/raycasting/raycasting.c \
		srcs/rendering/raycasting/raycasting_utils.c \
		srcs/rendering/minimap/minimap.c \
		srcs/rendering/minimap/minimap_utils.c \
		srcs/rendering/door/door.c \
		srcs/rendering/gun/gun.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

OS = $(shell uname)
FLAG_OPTI = -Ofast -ffast-math -O3
FLAG = $(LIBMLX) -Iinclude
ifeq ($(OS), Darwin)
    PROJECT_FLAGS = -L "/Users/$(USER)/.brew/opt/glfw/lib/" -lglfw -lm -framework Cocoa -framework OpenGL -framework IOKit $(FLAG_OPTI)
else ifeq ($(OS), Linux)
    PROJECT_FLAGS = -lglfw -lm -lGL $(FLAG_OPTI)
else
    $(error "Unsupported OS")
endif

CFLAGS = -I $(LIBFT) -Wall -Werror -Wextra
LDFLAGS = -lft -L $(LIBFT) -Wall -Werror -Wextra

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@gcc $(OBJS) $(LDFLAGS) $(FLAG) $(PROJECT_FLAGS) -o $(NAME)
	@echo "${GREEN}./${NAME} ${RED}map${NC}"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) $(FLAG_OPTI) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

run: all
	./$(NAME) rsrcs/maps/bonus.cub

.PHONY: all clean fclean re run bonus
