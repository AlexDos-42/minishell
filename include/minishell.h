#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "error.h"

typedef struct		s_all
{
	int	fct;
	char	*tab;
	char	*pwd;
	char	**env;
	char	ret;
	size_t	nb_env;
}			t_all;

/*
** --MAIN--
*/

int					main(int argc, char **argv, char** env);

#endif
