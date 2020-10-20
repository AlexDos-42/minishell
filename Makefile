_BOLD		=\e[1m
_R		=\e[0m

_RED		=\e[91m
_GREEN		=\e[92m
_YELLOW		=\e[93m
_BLUE		=\e[94m
_MAGENTA	=\e[35m
_CYAN		=\e[96m
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
		ft_export_solo.c \
		ft_utils.c \
		ft_utils_replace.c \


### Librairies ###
HEADERS = ./include/
INC = minishell.h
vpath %.h $(HEADERS)

### Sources ###
PATHSRCS = ./srcs
SRCS = $(addprefix $(PATHSRCS)/,$(SRC))

### Objets ###
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
vpath %.c $(PATHSRCS)

### Flags ###
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address 

### Libft ###
LIBS = ./libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: $(PATHSRCS)/%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -I $(HEADERS) -c $< -o $@
	@echo "$(_YELLOW)Compiling ➜$(_WHITE) $<$(_R)"

$(NAME): titre $(OBJ)
	@echo "$(_YELLOW)Compilation completed.$(_R)"
	@make -C libft/ > /dev/null
	@(gcc $(FLAGS) -I $(HEADERS) $(OBJ) -o $(NAME) $(LIBS))
	@(echo "$(_YELLOW)Executable $(NAME) created.$(_R)")

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

titre:
	@echo "\e[1;93mMinishell - 42 project -$(_R)"
	@echo "\e[1;93m________________________$(_R)"

.PHONY:	all clean fclean re titre
