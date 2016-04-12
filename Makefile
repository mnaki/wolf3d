# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmohamed <nmohamed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/05 14:47:20 by nmohamed          #+#    #+#              #
#    Updated: 2015/12/20 15:40:16 by nmohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		:=	compute.c control.c display.c main.c misc.c

CC		:=	gcc
NAME	:=	scop
INC		:=	-I./ -I$(HOME)/.brew/include/
OBJ		:=	$(SRC:.c=.o)
CFLAGS	:=	`sdl2-config --cflags` -Wall -Wextra #-Werror
LDFLAGS	:=	`sdl2-config --libs` -framework OpenGL -framework AppKit -lGLEW
#LDFLAGS	:=	`sdl2-config --libs` -lGLEW -glut -lGL

all		:	sdl2 $(NAME)

$(NAME)	:	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)  $(LDFLAGS) -lm

%.o		:	%.c
			@$(CC) -o $@ -c $(INC) $(CFLAGS) $^

clean	:
			-$(RM) $(OBJ)

fclean	:	clean
			-$(RM) $(OBJ)
			-$(RM) $(NAME)

re		:	clean all

sdl2		:
			brew install sdl2

.SILENT: all $(NAME) clean fclean re $(OBJ)
