# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/14 14:54:15 by qmebble           #+#    #+#              #
#    Updated: 2019/09/18 19:06:23 by qmebble          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_VI			=	main.c parse_turns.c vis_help.c push_to_render.c ants_move.c

SRC				=	../src/ft_card_reading.c ../src/ft_createroom.c ../src/ft_djkastra.c ../src/ft_suurballe.c\
				   	../src/ft_change.c ../src/ft_correct_main.c\
				   	../src/ft_name_find.c ../src/ft_correct_map.c ../src/ft_cleaning_struct.c\
					../src/ft_init.c\
					../src/ft_lemin_buff.c ../src/ft_null.c ../src/ft_redirection.c\
					../src/ft_connects.c ../src/ft_find_all_ways.c ../src/ft_add_room_link.c\
					../src/ft_find_of_ways_struct.c \
					../src/ft_lemin_fl.c ../src/ft_creat_duplicate.c\
					../src/ft_steps.c ../src/ft_additional_func.c ../src/ft_print.c\

INCLUDE =	visualise.h \
			../libft/libft.h

FLAGS = -Wall -Wextra -Werror
NAME = visualisator
FRAMEWORKS = -L/Users/asmall/.brew/lib -I/Users/asmall/.brew/include/SDL2 -D_THREAD_SAFE -lSDL2 -lSDL2_image -lSDL2_ttf
	# -I/Library/Frameworks/SDL2.framework/Headers -F ~/Library/Frameworks -framework SDL2 \
	# 			-I/Library/Frameworks/SDL2_image.framework/Headers -F ~/Library/Frameworks -framework SDL2_image \
	# 			-I/Library/Frameworks/SDL2_ttf.framework/Headers -F ~/Library/Frameworks -framework SDL2_ttf

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