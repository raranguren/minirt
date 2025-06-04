NAME		= miniRT
NAME_BONUS	= miniRT_bonus

CC	 		= gcc-12
CFLAGS		= -Wall -Werror -Wextra -g 

CPPFLAGS	= -Iincludes/ -Ilibft/header/ -Imlx -I/usr/include/X11/
LDFLAGS		= -Llibft/ -Lmlx -L/usr/lib/
LDLIBS		= -lft -lmlx -lX11 -lXext -lm

LIB			= libft/libft.a mlx

SRC_DIR	= src/
TMP_DIR = tmp/
TMP_DIRS	= $(addprefix $(TMP_DIR), $(filter-out $(curr), $(sort $(dir $(FILES)))))
TMP_DIRS += tmp/parsing

FILES	!= find src -type f -name "*.c" | grep -v parsing | sed 's/src\///g' | sed 's/\.c//g'

SRC_COMMON = $(FILES:%=$(SRC_DIR)%.c) \
	$(SRC_DIR)parsing/init_scene.c \
	$(SRC_DIR)parsing/object.c \
	$(SRC_DIR)parsing/utils.c \
	$(SRC_DIR)parsing/atoi_double.c \
	$(SRC_DIR)parsing/split_set.c \
	$(SRC_DIR)parsing/cam.c \
	$(SRC_DIR)parsing/amb_light.c \
	$(SRC_DIR)parsing/light.c \
	$(SRC_DIR)parsing/plane.c \
	$(SRC_DIR)parsing/sphere.c \
	$(SRC_DIR)parsing/cylinder.c \
	$(SRC_DIR)parsing/parse.c \

SRC = $(SRC_COMMON) \
	$(SRC_DIR)parsing/unique.c \

SRC_BONUS = $(SRC_COMMON) \
	$(SRC_DIR)parsing/unique_bonus.c \
	$(SRC_DIR)parsing/cone_bonus.c \

OBJ = $(SRC:$(SRC_DIR)%.c=$(TMP_DIR)%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_DIR)%.c=$(TMP_DIR)%.o)

MAKEFLAGS += --no-print-directory



all : $(NAME)

.PHONY :  clean fclean re bonus

$(TMP_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME) :  $(LIB) $(TMP_DIRS) $(OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS) :  $(LIB) $(TMP_DIRS) $(OBJ_BONUS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJ_BONUS) $(LDLIBS) -o $@ -D BONUS=1

clean :
	rm -rf $(TMP_DIR)
	rm -fr mlx
	$(MAKE) -C libft fclean --silent

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

$(TMP_DIRS) :
	@mkdir -p $(TMP_DIRS)

libft/libft.a :
	@$(MAKE) -C libft

mlx :
	git clone https://github.com/42paris/minilibx-linux.git mlx
	$(MAKE) -C mlx/ CC=gcc-12

#<--------------	DEV_TOOLS	------------->

.PHONY : vi dev watch prof

watch :
	source ~/42/42_venv/bin/activate
	watch -n1 "norminette | grep -v 'OK'; make"

vi vim :
	find . -name "*.c" -exec ctags {} +
	vim $(SRC) includes/* Makefile

gdb : all
	gdb --args ./$(NAME) scene_files/scene1.rt

dev : all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) scene_files/scene1.rt

prof : CFLAGS += -pg
prof : LDFLAGS += -pg
prof : re
	./$(NAME) scene_files/scene1.rt
	gprof $(NAME) -p
	$(MAKE) fclean
