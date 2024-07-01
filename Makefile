NAME = cub3D

LIBFT = libft
LIBMLX = MLX42/build/libmlx42.a 

OBJS_DIR = .objs
# SRCS = 	mandatory/main.c \
# 		mandatory/srcs/cub3d/init_and_unit/init_and_unit.c \
# 		mandatory/srcs/cub3d/parsing/check_file.c \
# 		mandatory/srcs/cub3d/parsing/check_map.c \
# 		mandatory/srcs/cub3d/window_and_event/window.c \
# 		mandatory/srcs/cub3d/window_and_event/event_hooks.c \
# 		mandatory/srcs/cub3d/utils/utils.c \
# 		mandatory/srcs/cub3d/rendering/raycasting/raycasting.c \
# 		mandatory/srcs/cub3d/rendering/raycasting/raycasting_utils.c \
# 		mandatory/srcs/cub3d/rendering/minimap/minimap.c \
# 		mandatory/srcs/cub3d/rendering/minimap/minimap_utils.c

SRCS = 		bonus/main.c \
				bonus/srcs/cub3d/init_and_unit/init_and_unit.c \
				bonus/srcs/cub3d/parsing/check_file.c \
				bonus/srcs/cub3d/parsing/check_map.c \
				bonus/srcs/cub3d/window_and_event/window.c \
				bonus/srcs/cub3d/window_and_event/event_hooks.c \
				bonus/srcs/cub3d/utils/utils.c \
				bonus/srcs/cub3d/rendering/raycasting/raycasting.c \
				bonus/srcs/cub3d/rendering/raycasting/raycasting_utils.c \
				bonus/srcs/cub3d/rendering/minimap/minimap.c \
				bonus/srcs/cub3d/rendering/minimap/minimap_utils.c \
				bonus/srcs/cub3d/rendering/door/door.c \
				bonus/srcs/cub3d/rendering/gun/gun.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))
OBJS_BONUS = $(addprefix $(OBJS_DIR)/, $(SRCS_BONUS:%.c=%.o))

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

CFLAGS = -I $(LIBFT) #-g -ggdb3 -fsanitize=address #-Wall -Werror -Wextra
LDFLAGS = -lft -L $(LIBFT) #-g -ggdb3 -fsanitize=address #-Wall -Werror -Wextra

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

# bonus: $(NAME)

# $(LIBFT)/libft.a:
# 	$(MAKE) -C $(LIBFT)

# $(NAME): $(OBJS_BONUS) $(LIBFT)/libft.a
# 	@gcc $(OBJS_BONUS) $(LDFLAGS) $(FLAG) $(PROJECT_FLAGS) -o $(NAME)
# 	@echo   "${GREEN}./${NAME} ${RED}map${NC}"

# $(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
# 	@gcc $(CFLAGS) $(FLAG_OPTI) $ -c $< -o $@

# $(OBJS_DIR):
# 	mkdir -p $(dir $(OBJS_BONUS))

clean:
	$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) rsrcs/maps/bonus.cub

.PHONY: all clean fclean re run
