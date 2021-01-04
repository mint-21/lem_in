# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmall <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/14 14:54:15 by asmall            #+#    #+#              #
#    Updated: 2019/09/18 19:06:23 by asmall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in

SRC				=	ft_card_reading.c ft_check_create_room.c \
				   	ft_change.c ft_correct_main.c \
				   	ft_correct_map.c ft_cleaning_struct.c\
					ft_zerodata.c\
					ft_lemin_buff.c ft_null.c \
					ft_check_connects.c ft_add_room_link.c\
					main.c\
					ft_creat_duplicate.c ft_terms.c\
					ft_additional_func.c ft_print.c\
					ft_count.c ft_path.c ft_bfs.c ft_add.c\
					ft_split.c ft_suurballe.c ft_merge.c\
					ft_collision.c ft_free.c ft_del.c ft_steps.c\
					ft_copy.c ft_bubble_sort_restore.c\
					ft_buf.c\

OBJ				=	ft_card_reading.o ft_check_create_room.o \
				   	ft_change.o ft_correct_main.o \
					ft_correct_map.o ft_cleaning_struct.o\
					ft_additional_func.o ft_zerodata.o\
					ft_lemin_buff.o ft_null.o \
					ft_check_connects.o \
					main.o ft_add_room_link.o\
					ft_creat_duplicate.o ft_print.o ft_terms.o\
					ft_count.o ft_path.o ft_bfs.o ft_add.o\
					ft_split.o ft_suurballe.o ft_merge.o\
					ft_collision.o ft_free.o ft_del.o\
					ft_copy.o ft_bubble_sort_restore.o ft_steps.o\
					ft_buf.o\


FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo Compiling Lem_in ...
	@gcc $(FLAGS) $(SRC) -include ../libft/libft.h -o $(NAME) ../libft/libft.a
	@mv $(NAME) ../$(NAME)

new:
	@echo Recompiling Lem_in ...
	@rm -rf ../$(NAME)
	@gcc $(FLAGS) $(SRC) -include ../libft/libft.h -o $(NAME) ../libft/libft.a
	@mv $(NAME) ../$(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf ../$(NAME)
	@rm -rf ../$(NAME).dSYM

re: fclean all
