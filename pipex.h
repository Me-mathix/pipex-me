#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int 	outfile;
	char	**cmd1;
	char	*path_cmd1;
	char	**cmd2;
	char	*path_cmd2;
	char	**path;
} t_pipex;

char	*mda_strjoin(char const *s1, char const *s2);
void 	ft_explosion(t_pipex *data, int i);
