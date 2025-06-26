NAME		= miniRT
NAME_BONUS	= miniRT_bonus

CC	 		= cc
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

FILES = \
	save/ft_putfloat_fd.c \
	save/put_obj_fd.c \
	save/save_scene.c \
	mlx/free.c \
	mlx/init.c \
	mlx/event.c \
	mlx/put_pixel.c \
	mlx/loop.c \
	utils/free.c \
	main.c \
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
	error/error.c \
	math/normalize.c \
	math/rotate.c \
	rays/caps.c \
	rays/utils.c \
	rays/sphere_bump_bonus.c \
	rays/vector2.c \
	rays/bump_bonus.c \
	rays/color2.c \
	rays/cone_bump_bonus.c \
	rays/quadratic.c \
	rays/plane_bump_bonus.c \
	rays/rays.c \
	rays/cone_bonus.c \
	rays/sphere.c \
	rays/light.c \
	rays/plane.c \
	rays/cylinder_bumb_bonus.c \
	rays/color.c \
	rays/cylinder.c \
	rays/sphere_checkered_bonus.c \
	rays/vector.c \
	debug/print.c \
	parsing/init_scene.c \
	parsing/object.c \
	parsing/utils.c \
	parsing/atoi_double.c \
	parsing/split_set.c \
	parsing/cam.c \
	parsing/amb_light.c \
	parsing/light.c \
	parsing/plane.c \
	parsing/sphere.c \
	parsing/cylinder.c \
	parsing/parse.c \

SRC = $(addprefix $(SRC_DIR), $(FILES)) \
	$(SRC_DIR)parsing/unique.c \

SRC_BONUS = $(addprefix $(SRC_DIR), $(FILES)) \
	$(SRC_DIR)parsing/unique_bonus.c \
	$(SRC_DIR)parsing/cone_bonus.c \
	$(SRC_DIR)parsing/init_scene_bonus.c \
	$(SRC_DIR)parsing/utils_bonus.c \

OBJ = $(SRC:$(SRC_DIR)%.c=$(TMP_DIR)%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_DIR)%.c=$(TMP_DIR_BONUS)%.o)

MAKEFLAGS += --no-print-directory

all: $(NAME)

.PHONY :  clean fclean re bonus demo demo_bonus

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

demo : all
	@clear
	@echo "Looping through all scenes in folder demo . . ."
	@for scene in demo/*.rt; do \
		if [ -f "$$scene" ]; then \
			echo "Showing scene: $$scene" ; \
			echo "(Close the window to open the next scene)" ; \
			echo ; \
			./$(NAME) $$scene > /dev/null ; \
		fi ; \
	done

demo_bonus : bonus
	@clear
	@echo "Looping through all scenes in folder demo_bonus . . ."
	@for scene in demo_bonus/*.rt; do \
		if [ -f "$$scene" ]; then \
			echo "Showing scene: $$scene" ; \
			echo "(Close the window to open the next scene)" ; \
			echo ; \
			./$(NAME_BONUS) $$scene > /dev/null ; \
		fi ; \
	done

#<--------------	DEV_TOOLS	------------->

.PHONY : vi dev watch prof ui

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
	-convert ~/Downloads/ui_camera.png ui_textures/ui_camera.xpm
	-convert ~/Downloads/ui_light.png ui_textures/ui_light.xpm
	-convert ~/Downloads/ui_amb_light.png ui_textures/ui_amb_light.xpm
	-convert ~/Downloads/ui_sphere.png ui_textures/ui_sphere.xpm
	-convert ~/Downloads/ui_plane.png ui_textures/ui_plane.xpm
	-convert ~/Downloads/ui_cylinder.png ui_textures/ui_cylinder.xpm
	-convert ~/Downloads/ui_cone.png ui_textures/ui_cone.xpm
	-rm -f ~/Downloads/ui_camera.png
	-rm -f ~/Downloads/ui_light.png
	-rm -f ~/Downloads/ui_amb_light.png
	-rm -f ~/Downloads/ui_sphere.png
	-rm -f ~/Downloads/ui_plane.png
	-rm -f ~/Downloads/ui_cylinder.png
	-rm -f ~/Downloads/ui_cone.png
