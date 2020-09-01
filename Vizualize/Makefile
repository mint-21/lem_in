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

SRC =	main.c \
		parse_turns.c \
		vis_help.c \
		push_to_render.c 

INCLUDE =	header/
LIBFT_HEAD = ../libft/
FLAGS = -Wall -Wextra -Werror
NAME = visualisator
# OS detection.
ifeq ($(OS),Windows_NT)
	detected_OS = Windows
else
	detected_OS = $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif
# Note: Current version only supports Linux and Mac OS.
ifeq ($(detected_OS),Darwin)
	FRAMEWORKS = -L$(SDL_LIBRARY) -lSDL2 -lSDL2_ttf
	FRAMEWORKS = -framework SDL2 -framework SDL2_ttf
	FLAGS += -F ~/Library/Frameworks 
	LDFLAGS += -I ~/Library/Frameworks/SDL2.framework/Headers -I ~/Library/Frameworks/SDL2_ttf.framework/Headers
else
	FRAMEWORKS = -lSDL2 -lSDL2_ttf -lSDL2_image
endif
				

all: $(NAME)

$(NAME):
	@echo Compiling Visualisator ...
	#@bash script.bash
	@gcc $(FLAGS) $(SRC) $(FRAMEWORKS)  ../libft/libft.a  -I $(INCLUDE) -I $(LIBFT_HEAD) -o $(NAME)
	@mv $(NAME) ../$(NAME)

new:
	@echo Recompiling Visualisator ...
	@rm -rf ../$(NAME)
	@gcc $(FLAGS) $(SRC) $(FRAMEWORKS)  ../libft/libft.a -I $(INCLUDE) -I $(LIBFT_HEAD) -o $(NAME)
	@mv $(NAME) ../$(NAME)

debug:
	@echo Recompiling Visualisator ...
	@rm -rf ../$(NAME)
	@rm -rf ../$(NAME).dSYM
	@gcc -g $(FLAGS) $(SRC) -I $(INCLUDE) ../libft.a $(FRAMEWORKS)
	@mv a.out ../$(NAME)
	@mv a.out.dSYM ../$(NAME).dSYM

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf ../$(NAME)
	@rm -rf ../$(NAME).dSYM

re: fclean all
