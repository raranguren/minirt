NAME		= miniRT

CC	 		= gcc-12
CFLAGS		= -Wall -Werror -Wextra -g 

CPPFLAGS	= -Iincludes/ -Ilibft/header/ -Imlx -I/usr/include/X11/
LDFLAGS		= -Llibft/ -Lmlx -L/usr/lib/
LDLIBS		= -lft -lmlx -lX11 -lXext -lm

LIB			= libft/libft.a mlx

SRC_DIR	= src/
TMP_DIR = tmp/
TMP_DIRS	= $(addprefix $(TMP_DIR), $(filter-out $(curr), $(sort $(dir $(FILES)))))

FILES	!= find src -type f -name "*.c" | sed 's/src\///g' | sed 's/\.c//g'

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(SRC:$(SRC_DIR)%.c=$(TMP_DIR)%.o)

MAKEFLAGS += --no-print-directory



all : $(NAME)

.PHONY :  clean fclean re 

$(TMP_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


$(NAME) :  $(LIB) $(TMP_DIRS) $(OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@

clean :
	rm -rf $(TMP_DIR)
	rm -fr mlx
	$(MAKE) -C libft fclean --silent

fclean : clean
	rm -f $(NAME)

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
