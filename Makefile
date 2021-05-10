# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmall <asmall@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 19:21:40 by asmall            #+#    #+#              #
#    Updated: 2021/05/10 16:52:31 by asmall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C ./libft/
	@make -C ./src/
	@make -C ./vis/

new_lem_in:
	@make -C ./src/ new

new_Vizualize:
	@make -C ./vis/ new

new: new_lem_in new_Vizualize

clean:
	@make -C ./src clean
	@make -C ./libft clean
	@make -C ./vis/ clean

fclean: clean
	@make -C ./libft fclean
	@rm -rf libft.a
	@make -C ./src fclean
	@make -C ./vis/ fclean

re: fclean all
