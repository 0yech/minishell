/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:57:02 by nrey              #+#    #+#             */
/*   Updated: 2025/03/14 13:48:13 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	git_str_replace(char branch[128], size_t bytes_read)
{
	while (bytes_read-- > 0)
	{
		if (branch[bytes_read] == '\n')
		{
			branch[bytes_read] = '\0';
			break ;
		}
	}
}

// TODO : Recursive git prompt
char	*get_git_branch(void)
{
	int		fd;
	char	branch[128];
	char	*branch_name;
	ssize_t	bytes_read;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, branch, sizeof(branch) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (NULL);
	branch[bytes_read] = '\0';
	git_str_replace(branch, bytes_read);
	if (ft_strncmp(branch, "ref: refs/heads/", 16) == 0)
		branch_name = ft_strdup(branch + 16);
	else
		branch_name = ft_strdup("(detached)");
	return (branch_name);
}

void	display_prompt(void)
{
	t_env	*cwd;
	char	*branch;

	branch = get_git_branch();
	cwd = env_get_key("PWD");
	if (cwd == NULL)
	{
		write(2, "minishell (display_prompt) - get_key: $PWD not set", 50);
		free(branch);
		return ;
	}
	if (branch)
	{
		printf("\033[1m\033[38;2;255;190;100m(git: %s)"
			"\033[38;2;160;240;130m%s"
			"\033[0m ", branch, cwd->value);
		free(branch);
	}
	else
		printf("\033[1m\033[38;2;160;240;130m%s\033[0m ", cwd->value);
}
