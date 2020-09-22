# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmall <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 19:21:40 by asmall            #+#    #+#              #
#    Updated: 2020/05/13 19:50:18 by asmall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C ./libft/
	@make -C ./src/
	@make -C ./Vizualize/

new_lem_in:
	@make -C ./src/ new

new_Vizualize:
	@make -C ./Vizualize/ new

new: new_lem_in new_Vizualize

clean:
	@make -C ./src clean
	@make -C ./libft clean
	@make -C ./Vizualize/ clean

fclean: clean
	@make -C ./libft fclean
	@rm -rf libft.a
	@make -C ./src fclean
	@make -C ./Vizualize/ fclean

re: fclean all