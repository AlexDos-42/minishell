_R			=\e[0m
_RED		=\e[91m
_GREEN		=\e[92m
_BLUE		=\e[94m
_WHITE		=\e[97m

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
		ft_suprguy.c \
		ft_parsing_next.c \
		ft_redirection_next.c \
		ft_redirection_bis.c \

HEADERS = ./include/
INC = minishell.h
vpath %.h $(HEADERS)

PATHSRCS = ./srcs
SRCS = $(addprefix $(PATHSRCS)/,$(SRC))

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))
vpath %.c $(PATHSRCS)

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address 

LIBS = ./libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -I $(HEADERS)  -c $< -o $@
	@echo "$(_GREEN)Compiling :$(_WHITE) $<$(_R)"

$(NAME): $(INC) $(OBJ)
	@echo "$(_GREEN)Compilation completed.$(_R)"
	@make -C libft/ > /dev/null
	@(gcc $(FLAGS) -I $(HEADERS)  -o $@ $(OBJ) $(LIBS))
	@(echo "$(_GREEN)Executable $(NAME) created.$(_R)")

clean:
	@echo "$(_BLUE)Clean$(_R)"
	@make clean -C ./libft/ > /dev/null
	@(rm -rf ./srcs/*.o)
	@(rm -rf $(OBJ_DIR))

fclean:	clean
	@echo "$(_BLUE)Fclean$(_R)"
	@make fclean -C ./libft/ > /dev/null
	@(rm -rf $(NAME))

re:	fclean all

.PHONY:	all clean fclean re
