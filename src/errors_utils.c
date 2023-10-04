/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:18 by asadanow          #+#    #+#             */
/*   Updated: 2023/01/04 15:34:27 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*  Prints error message if cmd not found and fd valid  */
void	error_access(int files[2], char **av, int err_idx)
{
	if (files[0] > 0 && (err_idx == 2 || err_idx == 5))
	{
		if (av[2][0] == '\0')
			ft_printf("Permission denied: \n");
		else
			cmd_message(av[2]);
		close(files[0]);
		files[0] = -1;
	}
	if (files[1] > 0 && (err_idx == 3 || err_idx == 5))
	{
		if (av[3][0] == '\0')
			ft_printf("Permission denied: \n");
		else
			cmd_message(av[3]);
		close(files[1]);
		files[1] = -1;
	}
}

void	cmd_message(char *av)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (!cmd)
		return ;
	ft_printf("Command not found: %s\n", cmd[0]);
	free_tab(cmd);
}

/*  Frees all allocated memory and exits process   */
void	clean_exit(char **cmds, char **paths)
{
	if (cmds)
		free_tab(cmds);
	if (paths)
		free_tab(paths);
	exit(EXIT_FAILURE);
}
