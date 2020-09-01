# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmall <asmall@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 19:21:40 by vfearles          #+#    #+#              #
#    Updated: 2020/05/13 19:50:18 by asmall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in
INC_NAME		=	lemin.h

LIB_PATH		=	libft/
LIB_INC_PATH	=	libft/
LIB_NAME		=	libft.a

SRC_PATH		=	src/
INC_PATH		=	inc/
OBJ_PATH		=	obj/

SRC_NAME		=	ft_lemin_read.c ft_rooms.c ft_ford.c ft_suurballe.c\
				   	ft_turn.c ft_error.c ft_correct_main.c\
				   	ft_findrooms.c ft_correct_map.c ft_free_data.c\
					ft_free_str_split.c\
					ft_lemin.c ft_null.c ft_redirection.c\
					ft_links.c ft_find_all_ways.c\
					ft_ways_ascending.c find_of_ways_struct.c main.c\
					ft_flags_lemin.c ft_creat_duplicate.c\
					ft_steps.c\

SRC				=	$(addprefix $(SRC_PATH), $(SRC_NAME))
INC				=	$(addprefix $(INC_PATH), $(INC_NAME))
OBJ				=	$(addprefix $(OBJ_PATH), $(SRC_NAME:.c=.o))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
IFLAGS			=	-I $(INC_PATH). -I $(LIB_PATH).
LFLAGS			=	-L $(LIB_PATH) -lft

LIB				=	make -C $(LIB_PATH)
VIS             =   make -C Vizualize/
.PHONY:	all clean fclean re lib

$(OBJ_PATH)%.o:		$(SRC_PATH)%.c $(INC)
					@mkdir -p $(OBJ_PATH)
					@$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

all:				$(NAME)

$(NAME):			$(OBJ)

					@$(LIB)
					#@$(VIS)
					@$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^ $(LFLAGS)
					@printf "%-54c\rDone !\n" ' '
					
clean:
					make clean -C $(LIB_PATH)
					rm -rf $(OBJ_PATH)

fclean:				clean
					make fclean -C $(LIB_PATH)
					rm -f $(NAME)

re:					fclean all
