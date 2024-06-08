NAME = Raycast

all:
	cc main.c ../MLX42/build/libmlx42.a ../srcs/libft/libft.a -I ../MLX42/include/ -I ../srcs/libft/includes/ -lglfw -lm -lGL -O3 -Ofast -ffast-math -o $(NAME)
run: all
	./Raycast