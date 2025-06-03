NAME		= miniRT

CC	 		= cc
CFLAGS		= -Wall -Werror -Wextra -g -O3

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
	$(MAKE) -C mlx/ 

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

coma 	:= ,
space 	:= $(empty) $(empty)
empty 	:=
curr	:=./

home :
	sudo docker run -it --rm -v "$$PWD":/mnt -w /mnt dev-env bash -c "make"

docker_run :
	sudo docker run -it --rm -v "$$PWD":/mnt -w /mnt dev-env
docker_set :
	echo "$$DOCKER" > Dockerfile
	sudo docker build -t dev-env .

export DOCKER
define DOCKER
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Paris

RUN apt update && apt install -y \
	    build-essential \
		    xorg-dev \
			    libbsd-dev \
				    && rm -rf /var/lib/apt/lists/*
endef
