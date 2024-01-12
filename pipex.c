/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:20:08 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/01/12 13:52:58 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *is_valid_path(char *cmd, char **path)
{
	int i;
	char *tmp;

	i = 0;
	while (path[i])
	{
		tmp = mda_strjoin(path[i], cmd);
		if (access(tmp, R_OK | X_OK) == 0)
			return(tmp);
		free(tmp);
		i++;
	}
	return(0);
}

void init_pipex(t_pipex *data, char **argv, char **envp)
{
	int i;

	data->cmd1 = ft_split(argv[2], ' ');
	data->cmd2 = ft_split(argv[3], ' ');
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	data->path = ft_split(envp[i] + 5,':');
	if (!data->cmd1 || !data->cmd2 || !data->path)
		ft_explosion(data, 1);
	data->path_cmd1 = is_valid_path(data->cmd1[0], data->path);
	if (!data->path_cmd1)
		ft_explosion(data, 2);
	data->path_cmd2 = is_valid_path(data->cmd2[0], data->path);
	if (!data->path_cmd2)
		ft_explosion(data, 3);
	data->infile = open(argv[1], O_RDONLY, 0777);
	data->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->infile < 0 || data->outfile < 0)
		ft_explosion(data, 4);
}

void kiddy(t_pipex *data, int *fd, char **env)
{
	dup2(data->infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	execve(data->path_cmd1, data->cmd1, env);
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(data->cmd1[0], 2);
	exit(0);
}

void daddy(t_pipex *data, int *fd, char **env)
{
	dup2(fd[0], 0);
	dup2(data->outfile, 1);
	close(fd[1]);
	execve(data->path_cmd2, data->cmd2, env);
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(data->cmd2[0], 2);
	exit(0);
}

int main(int argc, char **argv, char **envp)
{
	pid_t pid;
	int fd[2];
	t_pipex data;

	if (argc != 5)
		return(0);
	init_pipex(&data, argv, envp);
	pipe(fd);
	pid = fork();
	if (pid == -1)
		printf("FORK ERROR");
	if (pid == 0)
		kiddy(&data ,fd, envp);
	daddy(&data ,fd, envp);
	return (0);
}