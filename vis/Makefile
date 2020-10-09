# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmall <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/21 13:01:00 by asmall            #+#    #+#              #
#    Updated: 2020/09/21 13:01:04 by asmall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_VI			=	main.c ft_push_turns.c ft_help_funct.c ft_render_init.c\
					ft_render_info.c ft_ants_move.c

SRC				=	../src/ft_card_reading.c ../src/ft_createroom.c\
				   	../src/ft_correct_main.c ../src/ft_check_link.c\
					../src/ft_correct_map.c ../src/ft_cleaning_struct.c\
					../src/ft_init.c ../src/ft_null.c ../src/ft_redirection.c\
					../src/ft_connects.c ../src/ft_add_room_link.c\
					../src/ft_zerodata.c ../src/ft_additional_func.c\
					../src/ft_print.c\

INCLUDE =	visualise.h \
			../libft/libft.h

USER = $(shell whoami)
FLAGS = -Wall -Wextra -Werror
NAME = visualisator
FRAMEWORKS = -L/Users/$(USER)/.brew/lib -I/Users/$(USER)/.brew/include/SDL2 -D_THREAD_SAFE -lSDL2 -lSDL2_image -lSDL2_ttf


all: $(NAME)

$(NAME):
	@echo Compiling Visualisator ...
	@gcc $(FLAGS) $(SRC_VI) $(SRC) -I $(INCLUDE) $(FRAMEWORKS)  ../libft/libft.a
	@mv a.out ../$(NAME)

new:
	@echo Recompiling Visualisator ...
	@rm -rf ../$(NAME)
	@gcc $(FLAGS) $(SRC_VI) $(SRC) -I $(INCLUDE) $(FRAMEWORKS)  ../libft/libft.a
	@mv a.out ../$(NAME)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf ../$(NAME)
	@rm -rf ../$(NAME).dSYM

re: fclean all
