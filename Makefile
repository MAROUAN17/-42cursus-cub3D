CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = cc
LIBMLX = ./MLX42
SRCS =  mandatory/main.c mandatory/walls_utils.c mandatory/calculate_distance.c mandatory/horizontal_intersection.c mandatory/vertical_intersection.c mandatory/finding_wall.c \
	mandatory/calculations.c mandatory/minimap.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c mandatory/parse_map.c \
	mandatory/free_utils.c mandatory/parse_color.c mandatory/parse_textures.c mandatory/parse_elements.c mandatory/parse_utils.c
OBJS = ${addprefix mandatory/obj/, ${SRCS:.c=.o}}

SRCS_B =  bonus/initialization_bonus.c bonus/main_bonus.c bonus/walls_utils_bonus.c bonus/calculate_distance_bonus.c bonus/horizontal_intersection_bonus.c bonus/vertical_intersection_bonus.c bonus/finding_wall_bonus.c \
	bonus/calculations_bonus.c bonus/minimap_bonus.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c bonus/parse_map_bonus.c \
	bonus/free_utils_bonus.c bonus/parse_color_bonus.c bonus/parse_textures_bonus.c bonus/parse_elements_bonus.c \
	bonus/sprite_bonus.c bonus/movement_bonus.c bonus/parse_utils_bonus.c
OBJS_B = ${addprefix bonus/b_obj/, ${SRCS_B:.c=.o}}

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

HEADERS = -I ./MLX42/include/MLX42 -I ./MLX42/src/font
NAME = cub3D
NAME_B = cub3D_bonus
LIBS = ${LIBMLX}/build/libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
NEXT_LINE_H = get_next_line/get_next_line.h

all : libmlx ${NAME}

${LIBFT}:
	make -C ./libft
	make bonus -C ./libft

libmlx:
	@cmake ${LIBMLX} -B ${LIBMLX}/build && make -C ${LIBMLX}/build -j4

mandatory/obj/%.o: %.c mandatory/cub3d_header.h
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -o $@ -c $< ${HEADERS}

bonus/b_obj/%.o: %.c ./bonus/cub3d_header_b.h
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -o $@ -c $< ${HEADERS}

${NAME}: ${OBJ_LIBFT} ${OBJS} ${LIBFT} ${NEXT_LINE_H}
	${CC} ${CFLAGS} ${OBJS} ${LIBS} ${LIBFT} ${HEADERS} -o ${NAME}

bonus: libmlx ${OBJ_LIBFT} ${OBJS_B} ${LIBFT} ${NEXT_LINE_H} bonus/cub3d_header_b.h
	${CC} ${CFLAGS} ${OBJS_B} ${LIBS} ${LIBFT} ${HEADERS} -o ${NAME_B}

clean:
	rm -rf mandatory/obj
	rm -rf bonus/b_obj
	rm -rf ${OBJS} ${OBJS_B}
	rm -rf ${LIBMLX}/build
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)
	make fclean -C ./libft

re: clean all

.PHONY: all, clean, fclean, re, libmlx