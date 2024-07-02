NAME = cub3D
NAME_BONUS = cub4D

LIBFT = libft
LIBMLX = MLX42/build/libmlx42.a

OBJS_DIR = .objs

SRCS = 	mandatory/main.c \
		mandatory/srcs/init_and_unit/init_and_unit.c \
		mandatory/srcs/parsing/check_file.c \
		mandatory/srcs/parsing/check_map.c \
		mandatory/srcs/window_and_event/window.c \
		mandatory/srcs/window_and_event/event_hooks.c \
		mandatory/srcs/utils/utils.c \
		mandatory/srcs/rendering/raycasting.c \
		mandatory/srcs/rendering/raycasting_utils.c \

SRCS_BONUS = 	bonus/main.c \
				bonus/srcs/init_and_unit/init_and_unit.c \
				bonus/srcs/parsing/check_file.c \
				bonus/srcs/parsing/check_map.c \
				bonus/srcs/window_and_event/window.c \
				bonus/srcs/window_and_event/event_hooks.c \
				bonus/srcs/utils/utils.c \
				bonus/srcs/rendering/raycasting/raycasting.c \
				bonus/srcs/rendering/raycasting/raycasting_utils.c \
				bonus/srcs/rendering/minimap/minimap.c \
				bonus/srcs/rendering/minimap/minimap_utils.c \
				bonus/srcs/rendering/door/door.c \
				bonus/srcs/rendering/gun/gun.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))
OBJS_BONUS = $(addprefix $(OBJS_DIR)/, $(SRCS_BONUS:%.c=%.o))

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

CFLAGS = -I $(LIBFT) -g -ggdb3 -fsanitize=address -Wall -Werror -Wextra
LDFLAGS = -lft -L $(LIBFT) -g -ggdb3 -fsanitize=address -Wall -Werror -Wextra

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

bonus: $(OBJS_BONUS) $(LIBFT)/libft.a
	@gcc $(OBJS_BONUS) $(LDFLAGS) $(FLAG) $(PROJECT_FLAGS) -o $(NAME_BONUS)
	@echo "${GREEN}./${NAME_BONUS} ${RED}bonus_map${NC}"

clean:
	$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

run: all
	./$(NAME) rsrcs/maps/cub.cub

run2: bonus
	./$(NAME_BONUS) rsrcs/maps/bonus.cub

.PHONY: all clean fclean re run bonus
