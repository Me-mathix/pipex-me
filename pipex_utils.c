/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:22:54 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/01/12 00:49:48 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*mda_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	i = -1;
	j = -1;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if ((!s1) || (!s2))
		return (NULL);
	join = malloc((sizeof (char)) * (s1_len + s2_len) + 2);
	if (!join)
		return (NULL);
	while (++i < s1_len)
		join[i] = s1[i];
	join[i++] = '/';
	while (++j < s2_len)
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (join);
}

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void ft_explosion(t_pipex *data, int i)
{
	if (i >= 1)
	{
		ft_free(data->cmd1);
		ft_free(data->cmd2);
		ft_free(data->path);
	}
	if (i >= 2)
		free(data->path_cmd1);
	if (i >= 3)
		free(data->path_cmd2);
	exit(0);
}
