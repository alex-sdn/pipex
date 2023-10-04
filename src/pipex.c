/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:07:39 by asadanow          #+#    #+#             */
/*   Updated: 2023/01/03 19:07:50 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*  Open pipe and fork into two processes          */
/*  Parent waits for child to end before starting  */
void	pipex(int files[2], char **av, char **envp)
{
	int		pipefd[2];
	int		status;
	pid_t	process_id;
	char	**cmds;

	if (pipe(pipefd) < 0)
		return (perror("pipe"));
	process_id = fork();
	if (process_id < 0)
		return (perror("fork"));
	if (process_id == 0 && files[0] > 0)
	{
		cmds = ft_split(av[2], ' ');
		if (!cmds)
			return ;
		child_process(files[0], pipefd, cmds, envp);
	}
	else if (process_id > 0 && files[1] > 0)
	{
		wait(&status);
		cmds = ft_split(av[3], ' ');
		if (!cmds)
			return ;
		parent_process(files[1], pipefd, cmds, envp);
	}
}

/*  file1 replaces stdin, pipe[1] replaces stdout           */
/*  then try all possible paths for the cmd until executed  */
void	child_process(int f0, int pipefd[], char **cmds, char **envp)
{
	char	**paths;
	char	*pathcmd;
	int		i;

	i = 0;
	if (dup2(f0, 0) < 0)
		return (perror("dup2-1"));
	if (dup2(pipefd[1], 1) < 0)
		return (perror("dup2-2"));
	close(pipefd[0]);
	close(f0);
	paths = get_paths(envp);
	if (!paths)
		clean_exit(cmds, paths);
	while (paths[i])
	{
		pathcmd = ft_strjoin(paths[i], cmds[0]);
		if (!pathcmd)
			clean_exit(cmds, paths);
		execve(pathcmd, cmds, envp);
		i++;
		free(pathcmd);
	}
}

/*  pipe[0] replaces stdin, file2 replaces stdout           */
/*  then try all possible paths for the cmd until executed  */
void	parent_process(int f1, int pipefd[], char **cmds, char **envp)
{
	char	**paths;
	char	*pathcmd;
	int		i;

	i = 0;
	if (dup2(pipefd[0], 0) < 0)
		return (perror("dup2-3"));
	if (dup2(f1, 1) < 0)
		return (perror("dup2-4"));
	close(pipefd[1]);
	close(f1);
	paths = get_paths(envp);
	if (!paths)
		clean_exit(cmds, paths);
	while (paths[i])
	{
		pathcmd = ft_strjoin(paths[i], cmds[0]);
		if (!pathcmd)
			clean_exit(cmds, paths);
		execve(pathcmd, cmds, envp);
		i++;
		free(pathcmd);
	}
}

/*  First verify if files can be accessed  */
/*  then if commands can be accessed       */
int	main(int ac, char **av, char **envp)
{
	int		files[2];
	int		err_idx;

	if (ac != 5)
		return (0);
	files[0] = open(av[1], O_RDONLY);
	if (files[0] < 0)
		ft_printf("%s: %s\n", strerror(errno), av[1]);
	files[1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (files[1] < 0)
		ft_printf("%s: %s\n", strerror(errno), av[4]);
	err_idx = check_access(av, envp);
	if (err_idx > 0)
		error_access(files, av, err_idx);
	else if (err_idx < 0)
		exit(EXIT_FAILURE);
	if ((files[0] > 0 || files[1] > 0) && err_idx < 3)
		pipex(files, av, envp);
	exit(EXIT_FAILURE);
	return (0);
}
