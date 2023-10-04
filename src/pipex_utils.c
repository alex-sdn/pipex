/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:07:54 by asadanow          #+#    #+#             */
/*   Updated: 2023/01/03 19:07:56 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*  Finds string with paths in envp              */
/*  and splits them adding '/' at end            */
/*  If no env, return empty string for abs path  */
char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
	{
		paths = malloc(sizeof(char *) * 2);
		if (!paths)
			return (NULL);
		paths[0] = malloc(sizeof(char) * 1);
		if (!paths[0])
			return (free(paths), NULL);
		paths[0][0] = '\0';
		paths[1] = 0;
	}
	else
		paths = ft_split_pipex(envp[i] + 5, ':');
	return (paths);
}

/*  Returns 0 if cmds exist, -1 if malloc error   */
/*  2 if cmd1 can't be accessed, 3 if cmd2 can't  */
/*  or 5 if both can't be accessed                */
int	check_access(char **av, char **envp)
{
	char	**paths;
	char	**cmd;
	int		res;
	int		i;

	i = 1;
	res = 0;
	paths = get_paths(envp);
	if (!paths)
		return (-1);
	while (++i < 4)
	{
		if (av[i][0] == '\0')
			res += i;
		else
		{
			cmd = ft_split(av[i], ' ');
			if (!cmd)
				return (free_tab(paths), -1);
			res += check_access_loop(cmd[0], paths) * i;
			free_tab(cmd);
		}
	}
	free_tab(paths);
	return (res);
}

int	check_access_loop(char *cmd, char **paths)
{
	char	*pathcmd;
	int		i;

	i = 0;
	while (paths[i])
	{
		pathcmd = ft_strjoin(paths[i], cmd);
		if (!pathcmd)
			return (-10);
		if (access(pathcmd, X_OK) == 0)
			break ;
		free(pathcmd);
		i++;
	}
	if (!paths[i])
		return (1);
	free(pathcmd);
	return (0);
}

/*  Proper free for **char   */
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
