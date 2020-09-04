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

SRC_VI			=	main.c parse_turns.c vis_help.c push_to_render.c

SRC				=	../src/ft_lemin_read.c ../src/ft_rooms.c ../src/ft_djkastra.c ../src/ft_suurballe.c\
				   	../src/ft_turn.c ../src/ft_error.c ../src/ft_correct_main.c\
				   	../src/ft_findrooms.c ../src/ft_correct_map.c ../src/ft_free_data.c\
					../src/ft_free_str_split.c ../src/ft_init.c\
					../src/ft_lemin_buff.c ../src/ft_null.c ../src/ft_redirection.c\
					../src/ft_links.c ../src/ft_find_all_ways.c\
					../src/find_of_ways_struct.c\
					../src/ft_flags_lemin.c ../src/ft_creat_duplicate.c\
					../src/ft_steps.c ../src/ft_additional_func.c\

INCLUDE =	visualise.h \
			../libft/libft.h

FLAGS = -Wall -Wextra -Werror
NAME = visualisator
FRAMEWORKS =	-I/Library/Frameworks/SDL2.framework/Headers -F ~/Library/Frameworks -framework SDL2 \
				-I/Library/Frameworks/SDL2_image.framework/Headers -F ~/Library/Frameworks -framework SDL2_image \
				-I/Library/Frameworks/SDL2_ttf.framework/Headers -F ~/Library/Frameworks -framework SDL2_ttf

all: $(NAME)

$(NAME):
	@echo Compiling Visualisator ...
	@bash script.bash
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