CFLAGS =-Wall -Werror -Wextra
NAME = Cub3D

SRC_FILE = cub3d.c
GNL_FILE = get_next_line.c get_next_line_utils.c

LIB_PATH = libft/
LIB_FILE = ft_split.c \
ft_calloc.c \
ft_bzero.c \
ft_strjoin.c \
ft_atoi.c \
ft_putstr_fd.c \
ft_putchar_fd.c

GNL_PATH = gnl/
INC= cub3d.h
SRC = ${SRC_FILE} ${addprefix ${GNL_PATH}, $(GNL_FILE)} ${addprefix ${LIB_PATH}, $(LIB_FILE)}
OBJS = ${SRC:%.c=%.o}
FRAMEWORK = -framework OpenGL -framework AppKit
LIB = minilibx/

all: ${NAME}

$(NAME): ${OBJS} ${INC}
	@gcc ${FLAGS} -I include -g -l mlx ${FRAMEWORK} ${OBJS} -o ${NAME}

%.o : %.c
	@echo Compiling $<
	gcc $(FLAGS) -c -I include/ $< -o $@

clean:
	rm -f ${OBJS} ${BONUS}

fclean: clean
	rm ${NAME}

bonus :

re: clean all