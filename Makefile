# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alesanto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 17:02:25 by alesanto          #+#    #+#              #
#    Updated: 2020/04/10 16:03:47 by alesanto         ###   ########.fr        #
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
		ft_unset.c \
		ft_replace.c \
		ft_pipe.c \
		ft_pipeerror.c \
		ft_redirection.c \
		ft_splitslash.c \
		ft_splitspace.c \
		ft_exec.c \
		ft_splitbuiltin.c \
		ft_strtrimslash.c \
		ft_utils_exec.c \
		ft_utils_export.c \
		ft_guillemet.c \
		ft_utils_pipeerror.c \

PATHSRCS = srcs

HEADERS = ./include

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address 

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
