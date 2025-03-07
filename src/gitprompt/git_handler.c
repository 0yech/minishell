/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:57:02 by nrey              #+#    #+#             */
/*   Updated: 2025/03/07 09:39:53 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	git_str_replace(char branch[128], int bytes_read)
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
	char	cwd[1024];
	char	*branch;

	branch = get_git_branch();
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	if (branch)
	{
		printf("\033[1m\033[38;2;255;190;100m(git: %s)"
			"\033[38;2;160;240;130m%s"
			"\033[0m ", branch, cwd);
		free(branch);
	}
	else
		printf("%s ", cwd);
}
