CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = cc
LIBMLX = MLX42
SRCS =  main.c walls_utils.c calculate_distance.c horizontal_intersection.c vertical_intersection.c finding_wall.c \
	calculations.c minimap.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parse_map.c \
	free_utils.c
OBJS = ${addprefix obj/, ${SRCS:.c=.o}}
LIBFT = ./libft/libft.a
SRCS_LIBFT = libft/ft_isprint.c libft/ft_isdigit.c libft/ft_isascii.c libft/ft_isalpha.c \
	libft/ft_isalnum.c libft/ft_bzero.c libft/ft_strlen.c libft/ft_memset.c libft/ft_memcpy.c \
	libft/ft_memmove.c libft/ft_strlcpy.c libft/ft_strlcat.c  libft/ft_toupper.c libft/ft_tolower.c \
	libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c \
	libft/ft_strnstr.c libft/ft_atoi.c libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c \
	libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c \
	libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c \
	libft/ft_putnbr_fd.c
OBJ_LIBFT = ${SRCS_LIBFT:.c=.o}
HEADERS = -I MLX42/include/MLX42 -I MLX42/src/font
NAME = cub3D
LIBS = ${LIBMLX}/build/libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
NEXT_LINE_H = get_next_line/get_next_line.h

all : libmlx ${NAME}

${LIBFT}:
	make -C ./libft
	make bonus -C ./libft

libmlx:
	@cmake ./${LIBMLX} -B ${LIBMLX}/build && make -C ${LIBMLX}/build -j4

obj/%.o: %.c ./cub3d_header.h
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -o $@ -c $< ${HEADERS}

${NAME}: ${OBJ_LIBFT} ${OBJS} ${LIBFT} ${NEXT_LINE_H}
	${CC} ${CFLAGS} ${OBJS} ${LIBS} ${LIBFT} ${HEADERS} -o ${NAME}

clean:
	rm -rf obj
	rm -rf ${OBJS}
	rm -rf ${LIBMLX}/build
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

re: clean all

.PHONY: all, clean, fclean, re, libmlx