NAME = libft.a

SRCS = ft_atoi.c \
       ft_isalpha.c \
       ft_bzero.c \
       ft_isascii.c \
       ft_isalnum.c \
       ft_isdigit.c \
       ft_calloc.c \
       ft_isprint.c \
       ft_itoa.c \
       ft_memccpy.c \
       ft_memchr.c \
       ft_memcpy.c \
       ft_memcmp.c \
       ft_memset.c \
       ft_putchar_fd.c \
       ft_putendl_fd.c \
       ft_putstr_fd.c \
       ft_strchr.c \
       ft_putnbr_fd.c \
       ft_strlcat.c \
       ft_strdup.c \
       ft_strjoin.c \
       ft_strlen.c \
       ft_strncmp.c \
       ft_split.c \
       ft_strrchr.c \
       ft_substr.c \
       ft_strlcpy.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strtrim.c \
       ft_strmapi.c \
       ft_realloc.c \
       ft_strnstr.c \
       ft_memmove.c \
       ft_lstadd_back.c \
       ft_lstadd_front.c \
       ft_lstdelone.c \
       ft_lstiter.c \
       ft_lstclear.c \
       ft_lstlast.c \
       ft_lstnew.c \
       ft_lstsize.c \
       ft_lstmap.c \
       get_next_line.c \
       ft_strdel.c \
       ft_suprspace.c \
       ft_cjoin.c \
	   ft_fpower.c \
       ft_printf/ft_utile.c \
       ft_printf/ft_printf.c \
       ft_printf/ft_parsing.c \
       ft_printf/application.c \
       ft_printf/ft_putstr_pf.c \

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

.c.o : $(SRCS)
	@(gcc -c $(FLAGS) -I . $^ -o $(^:.c=.o))

$(NAME): $(OBJS) 
	@echo "Compilation de la Libft..."
	@(ar rc $(NAME) $(OBJS))
	@(ranlib $(NAME))

clean:
	@(rm -rf *.o)
	@(rm -rf ft_printf/*.o)

fclean:	clean
	@(rm -rf $(NAME))

re:	fclean all

.PHONY:	all clean fclean re
