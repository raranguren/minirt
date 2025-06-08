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
TMP_DIRS += $(TMP_DIR)/parsing
TMP_DIR_BONUS = tmp2/
TMP_DIRS_BONUS= $(addprefix $(TMP_DIR_BONUS), $(filter-out $(curr), $(sort $(dir $(FILES)))))
TMP_DIRS_BONUS += $(TMP_DIR_BONUS)/parsing

HEADERS = \
	includes/defines.h \
	includes/minirt.h \
	includes/typedefs.h \

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
	$(SRC_DIR)parsing/init_scene_bonus.c \
	$(SRC_DIR)parsing/utils_bonus.c \

OBJ = $(SRC:$(SRC_DIR)%.c=$(TMP_DIR)%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_DIR)%.c=$(TMP_DIR_BONUS)%.o)

MAKEFLAGS += --no-print-directory

all: $(NAME)

.PHONY :  clean fclean re bonus

$(TMP_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -D BONUS=0

$(TMP_DIR_BONUS)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -D BONUS=1

$(NAME) :  $(LIB) $(TMP_DIRS) $(OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@

$(OBJ) $(OBJ_BONUS) : $(HEADERS) Makefile

bonus: $(NAME_BONUS)

$(NAME_BONUS) :  $(LIB) $(TMP_DIRS_BONUS) $(OBJ_BONUS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJ_BONUS) $(LDLIBS) -o $@


clean :
	rm -rf $(TMP_DIR) $(TMP_DIR_BONUS)
	rm -fr mlx
	$(MAKE) -C libft fclean --silent

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

$(TMP_DIRS) :
	@mkdir -p $(TMP_DIRS)

$(TMP_DIRS_BONUS) :
	@mkdir -p $(TMP_DIRS_BONUS)

libft/libft.a :
	$(MAKE) -C libft --silent

mlx :
	git clone -q https://github.com/42paris/minilibx-linux.git mlx
	$(MAKE) -C mlx/ CC=$(CC) 2>/dev/null >/dev/null

#<--------------	DEV_TOOLS	------------->

.PHONY : vi dev watch prof ui

watch :
	source ~/42/42_venv/bin/activate
	watch -n1 "norminette | grep -v 'OK'; make"

vi vim :
	find . -name "*.c" -exec ctags {} +
	vim $(SRC) $(SRC_BONUS) includes/* Makefile

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
	rm -f gmon.out

ui :
	convert ~/Downloads/ui_camera.png ui_textures/ui_camera.xpm
	convert ~/Downloads/ui_light.png ui_textures/ui_light.xpm
	convert ~/Downloads/ui_amb_light.png ui_textures/ui_amb_light.xpm
	convert ~/Downloads/ui_sphere.png ui_textures/ui_sphere.xpm
	convert ~/Downloads/ui_plane.png ui_textures/ui_plane.xpm
	convert ~/Downloads/ui_cylinder.png ui_textures/ui_cylinder.xpm
	convert ~/Downloads/ui_cone.png ui_textures/ui_cone.xpm
	rm -f ~/Downloads/ui_camera.png
	rm -f ~/Downloads/ui_light.png
	rm -f ~/Downloads/ui_amb_light.png
	rm -f ~/Downloads/ui_sphere.png
	rm -f ~/Downloads/ui_plane.png
	rm -f ~/Downloads/ui_cylinder.png
	rm -f ~/Downloads/ui_cone.png
