NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
NC=\033[0m

LIBFT_SRCS =	srcs/libft/ft_isalpha.c \
				srcs/libft/ft_isdigit.c \
				srcs/libft/ft_is_string_number.c \
				srcs/libft/ft_isalnum.c \
				srcs/libft/ft_isascii.c \
				srcs/libft/ft_isprint.c \
				srcs/libft/ft_isspace.c \
				srcs/libft/ft_strlen.c \
				srcs/libft/ft_memset.c \
				srcs/libft/ft_bzero.c \
				srcs/libft/ft_memcpy.c \
				srcs/libft/ft_memmove.c \
				srcs/libft/ft_strlcpy.c \
				srcs/libft/ft_strlcat.c \
				srcs/libft/ft_toupper.c \
				srcs/libft/ft_tolower.c \
				srcs/libft/ft_strchr.c \
				srcs/libft/ft_strrchr.c \
				srcs/libft/ft_strncmp.c \
				srcs/libft/ft_memchr.c \
				srcs/libft/ft_memcmp.c \
				srcs/libft/ft_strnstr.c \
				srcs/libft/ft_atoi.c \
				srcs/libft/ft_strtol.c \
				srcs/libft/ft_calloc.c \
				srcs/libft/ft_strdup.c \
				srcs/libft/ft_strndup.c \
				srcs/libft/ft_substr.c \
				srcs/libft/ft_strjoin.c \
				srcs/libft/ft_strtrim.c \
				srcs/libft/ft_split.c \
				srcs/libft/ft_itoa.c \
				srcs/libft/ft_strmapi.c \
				srcs/libft/ft_striteri.c \
				srcs/libft/ft_putstr_fd.c \
				srcs/libft/ft_putchar_fd.c \
				srcs/libft/ft_putendl_fd.c \
				srcs/libft/ft_putnbr_fd.c \
				srcs/libft/ft_lstnew.c \
				srcs/libft/ft_lstadd_front.c \
				srcs/libft/ft_lstsize.c \
				srcs/libft/ft_lstlast.c \
				srcs/libft/ft_lstadd_back.c \
				srcs/libft/ft_lstdelone.c \
				srcs/libft/ft_lstclear.c \
				srcs/libft/ft_lstiter.c \
				srcs/libft/ft_lstmap.c \
				srcs/libft/ft_splitdup.c \
				srcs/libft/ft_splitlen.c \
				srcs/libft/ft_read.c \
				srcs/libft/ft_strjoin_free.c \
				srcs/libft/ft_strjoin_free_free.c \
				srcs/libft/ft_ischarin.c \
				srcs/libft/ft_strcmp.c \
				srcs/libft/ft_free_matrix.c \
				srcs/libft/ft_free.c \
				srcs/libft/ft_splitjoin.c \
				srcs/libft/ft_splittrim.c \
				srcs/libft/ft_putsplit.c \
				srcs/libft/ft_strjoinchar_free.c \
				srcs/libft/ft_null.c \

GNL_SRCS = 		srcs/gnl/get_next_line.c

PRINTF_SRCS = 	srcs/printf/ft_printf.c \
				srcs/printf/srcs/ft_putchar_fd_l.c \
				srcs/printf/srcs/ft_putstr_fd_l.c \
				srcs/printf/srcs/ft_putnbr_fd_l.c \
				srcs/printf/srcs/ft_hexadecimal.c \
				srcs/printf/srcs/ft_pointer.c \
				srcs/printf/srcs/ft_u_putnbr_fd_l.c

SRCS = $(LIBFT_SRCS) $(GNL_SRCS) $(PRINTF_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "${GREEN}Compilation complete.${NC}"

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "${YELLOW}Library $(NAME) created.${NC}"

%.o: %.c
	@echo "${RED}Compiling $<...${NC}"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "${GREEN}Object files cleaned.${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}Library removed.${NC}"

re: fclean all

.PHONY: all clean fclean re