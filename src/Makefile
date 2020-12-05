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
					count.c \

OBJ				=	ft_card_reading.o ft_check_create_room.o \
				   	ft_change.o ft_correct_main.o \
					ft_correct_map.o ft_cleaning_struct.o\
					ft_additional_func.o ft_zerodata.o\
					ft_lemin_buff.o ft_null.o \
					ft_check_connects.o \
					main.o ft_add_room_link.o\
					ft_creat_duplicate.o ft_print.o ft_terms.o\

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
