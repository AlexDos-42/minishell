# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alesanto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 17:02:25 by alesanto          #+#    #+#              #
#    Updated: 2020/02/04 18:02:09 by alesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

SRC =		main.c \
		ft_parsing.c \
		ft_init.c \
		ft_cd.c \
		ft_echo.c \
		ft_env.c \
		ft_exit.c \
		ft_pwd.c \
		ft_export.c \

PATHSRCS = srcs

HEADERS = ./include

FLAGS = -Wall -Wextra -Werror 

SRCS = $(addprefix $(PATHSRCS)/,$(SRC))
LIBS = ./libft/libft.a

all: $(NAME)

$(NAME):
	@echo "Compilation..."
	@(make re -C libft/)
	@(gcc $(FLAGS) $(SRCS) $(LIBS) -o $(NAME))
	@(echo "Compilation terminée")

clean:
	@echo "Clean"
	@(make clean -C ./libft/)

fclean:	clean
	@echo "Fclean"
	@(make fclean -C ./libft/)
	@(rm -rf $(NAME))

re:	fclean all

.PHONY:	all clean fclean re
