/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:08:25 by asadanow          #+#    #+#             */
/*   Updated: 2023/01/03 19:08:31 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

/*  Libft  */
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *s);
int		ft_printf(const char *s, ...);

/*  Utils  */
char	**ft_split_pipex(char const *s, char c);
char	**get_paths(char **envp);
int		check_access(char **av, char **envp);
int		check_access_loop(char *cmd, char **paths);
void	free_tab(char **tab);

/*  Errors  */
void	error_access(int files[2], char **av, int err_idx);
void	cmd_message(char *av);
void	clean_exit(char **cmds, char **paths);

/*  Main  */
int		main(int ac, char **av, char **envp);
void	pipex(int files[2], char **av, char **envp);
void	child_process(int f1, int pipefd[], char **cmds, char **envp);
void	parent_process(int f2, int pipefd[], char **cmds, char **envp);

#endif
