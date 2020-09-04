# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmall <asmall@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/14 14:54:15 by asmall            #+#    #+#              #
#    Updated: 2019/09/18 19:06:23 by asmall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in

SRC				=	ft_lemin_read.c ft_rooms.c ft_djkastra.c ft_suurballe.c\
				   	ft_turn.c ft_error.c ft_correct_main.c\
				   	ft_findrooms.c ft_correct_map.c ft_free_data.c\
					ft_free_str_split.c ft_init.c\
					ft_lemin_buff.c ft_null.c ft_redirection.c\
					ft_links.c ft_find_all_ways.c\
					find_of_ways_struct.c main.c\
					ft_flags_lemin.c ft_creat_duplicate.c\
					ft_steps.c ft_additional_func.c\

OBJ				=	ft_lemin_read.o ft_rooms.o ft_djkastra.o ft_suurballe.o\
				   	ft_turn.o ft_error.o ft_correct_main.o\
				   	ft_findrooms.o ft_correct_map.o ft_free_data.o\
					ft_free_str_split.o ft_additional_func.o\
					ft_lemin_buff.o ft_null.o ft_redirection.o\
					ft_links.o ft_find_all_ways.o ft_init.o\
					find_of_ways_struct.o main.o ft_steps.\
					ft_flags_lemin.o ft_creat_duplicate.o\

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
