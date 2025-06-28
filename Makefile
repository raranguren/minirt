NAME		= miniRT
NAME_BONUS	= miniRT_bonus

CC	 		= cc
CPPFLAGS	= -Iincludes/ -Ilibft/header/ -Imlx -I/usr/include/X11/
CFLAGS		= -Wall -Werror -Wextra -g 
LDFLAGS		= -Llibft/ -Lmlx -L/usr/lib/
LDLIBS		= -lft -lmlx -lX11 -lXext -lm

LIB			= libft/libft.a mlx
SRC_DIR	= src/
TMP_DIR = tmp/
TMP_DIR_BONUS = tmp/bonus/
HEADERS = \
	includes/defines.h \
	includes/minirt.h \
	includes/typedefs.h \

FILES = \
	main.c \
	error.c \
	free.c \
	parsing/parse.c \
	parsing/object.c \
	parsing/utils.c \
	parsing/init_scene.c \
	parsing/atoi_double.c \
	parsing/split_set.c \
	parsing/cam.c \
	parsing/amb_light.c \
	parsing/light.c \
	parsing/plane.c \
	parsing/sphere.c \
	parsing/cylinder.c \
	edit/gui_labels.c \
	edit/edit.c \
	edit/gui_numbers.c \
	edit/mouse.c \
	edit/gui.c \
	edit/edit_select.c \
	edit/edit_init.c \
	edit/snap_obj.c \
	edit/color.c \
	edit/gui_color.c \
	save/ft_putfloat_fd.c \
	save/put_obj_fd.c \
	save/save_scene.c \
	mlx/free.c \
	mlx/init.c \
	mlx/event.c \
	mlx/put_pixel.c \
	mlx/loop.c \
	rays/caps.c \
	rays/utils.c \
	rays/quadratic.c \
	rays/rays.c \
	rays/sphere.c \
	rays/light.c \
	rays/plane.c \
	rays/cylinder.c \
	math/vector.c \
	math/vector2.c \
	math/color.c \
	math/color2.c \
	math/rotate.c \
	math/normalize.c \

FILES_NO_BONUS = $(FILES) \
	parsing/unique.c \

FILES_BONUS = $(FILES) \
	parsing/unique_bonus.c \
	parsing/cone_bonus.c \
	parsing/init_scene_bonus.c \
	parsing/utils_bonus.c \
	rays/sphere_bump_bonus.c \
	rays/bump_bonus.c \
	rays/sphere_checkered_bonus.c \
	rays/cylinder_bumb_bonus.c \
	rays/plane_bump_bonus.c \
	rays/cone_bonus.c \
	rays/cone_bump_bonus.c \

SRC = $(addprefix $(SRC_DIR), $(FILES_NO_BONUS))
OBJ = $(SRC:$(SRC_DIR)%.c=$(TMP_DIR)%.o)
SRC_BONUS = $(addprefix $(SRC_DIR), $(FILES_BONUS))
OBJ_BONUS = $(SRC_BONUS:$(SRC_DIR)%.c=$(TMP_DIR_BONUS)%.o)
TMP_DIRS = $(addprefix $(TMP_DIR), $(filter-out $(curr), $(sort $(dir $(FILES)))))
TMP_DIRS_BONUS= $(addprefix $(TMP_DIR_BONUS), $(filter-out $(curr), $(sort $(dir $(FILES)))))
MAKEFLAGS += --no-print-directory

all: $(NAME)

.PHONY : clean fclean re bonus demo

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

$(TMP_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -D BONUS=0

$(TMP_DIR_BONUS)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -D BONUS=1

libft/libft.a :
	$(MAKE) -C libft --silent

mlx :
	git clone -q https://github.com/42paris/minilibx-linux.git mlx
	$(MAKE) -C mlx/ CC=$(CC) 2>/dev/null >/dev/null

demo : $(NAME) $(NAME_BONUS)
	@clear
	@echo "Looping through example scenes . . ."
	@for scene in scenes/a_*.rt; do \
		if [ -f "$$scene" ]; then \
			echo "Showing scene: $$scene" ; \
			echo "(Close the window to open the next scene)" ; \
			echo ; \
			./$(NAME) $$scene > /dev/null ; \
		fi ; \
	done
	@echo "Looping through BONUS scenes . . ."
	@for scene in scenes/b_*.rt; do \
		if [ -f "$$scene" ]; then \
			echo "Showing scene: $$scene" ; \
			echo "(Close the window to open the next scene)" ; \
			echo ; \
			./$(NAME_BONUS) $$scene > /dev/null ; \
		fi ; \
	done

.PHONY : vi dev watch prof ui

vi vim :
	find . -name "*.c" -exec ctags {} +
	vim $(SRC) $(SRC_BONUS) includes/* Makefile
	rm -fr tags

gdb : all
	gdb --args ./$(NAME) snapshot.rt

dev : all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
		./$(NAME_BONUS) snapshot.rt

prof : CFLAGS += -pg
prof : LDFLAGS += -pg
prof : fclean bonus
	./$(NAME_BONUS) snapshot.rt
	gprof $(NAME_BONUS) -p
	$(MAKE) fclean
	rm -f gmon.out
