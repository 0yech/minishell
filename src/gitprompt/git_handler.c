/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:57:02 by nrey              #+#    #+#             */
/*   Updated: 2025/04/07 17:59:39 by nrey             ###   ########.fr       */
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

char	*cut_pwd(char *path)
{
	int		i;
	char	*p;

	p = NULL;
	if (!path)
		return (NULL);
	i = ft_strlen(path) - 1;
	if (i <= 0)
		return (NULL);
	if (ft_strchr(path, '/'))
	{
		while (i > 0 && path[i] != '/')
			i--;
		if (path[i] == '/')
		{
			p = malloc(i + 1);
			if (!p)
				return (NULL);
			ft_strlcpy(p, path, i + 1);
			return (p);
		}
	}
	return (NULL);
}

static int	try_open_head(char *dir)
{
	char	*head_path;
	int		fd;

	head_path = ft_strjoin(dir, "/.git/HEAD");
	if (!head_path)
		return (-1);
	fd = open(head_path, O_RDONLY);
	free(head_path);
	return (fd);
}

static int	is_folder_root(char *path)
{
	return (ft_strlen(path) == 1 && ft_strncmp(path, "/", 1) == 0);
}

int	find_git_head(void)
{
	t_env	*pwd;
	char	*dir;
	int		fd;
	char	*new_dir;

	pwd = env_get_key("PWD");
	if (!pwd || !pwd->value)
		return (-1);
	dir = ft_strdup(pwd->value);
	if (!dir)
		return (-1);
	while (1)
	{
		fd = try_open_head(dir);
		if (fd >= 0)
			return (free(dir), fd);
		if (is_folder_root(dir))
			break ;
		new_dir = cut_pwd(dir);
		free(dir);
		if (!new_dir)
			return (-1);
		dir = new_dir;
	}
	return (-1);
}

// TODO : Recursive git prompt
char	*get_git_branch(void)
{
	int		fd;
	char	branch[128];
	char	*branch_name;
	ssize_t	bytes_read;

	fd = find_git_head();
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
