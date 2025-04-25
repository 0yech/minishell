/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_git.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:59:55 by fireinside        #+#    #+#             */
/*   Updated: 2025/04/17 18:12:08 by nrey             ###   ########.fr       */
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
				return (perror("minishell (cut_pwd) - malloc"), NULL);
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
		return (perror("minishell (try_open_head) - malloc"), -1);
	fd = open(head_path, O_RDONLY);
	free(head_path);
	return (fd);
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
		return (perror("minishell (find_git_head) - malloc"), -1);
	while (1)
	{
		fd = try_open_head(dir);
		if (fd >= 0)
			return (free(dir), fd);
		if (ft_strlen(dir) == 1 && ft_strncmp(dir, "/", 1) == 0)
			return (free(dir), -1);
		new_dir = cut_pwd(dir);
		free(dir);
		if (!new_dir)
			return (-1);
		dir = new_dir;
	}
}

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
	if (bytes_read == -1)
		return (perror("minishell (get_git_branch) - read"), NULL);
	if (close(fd) == -1)
		perror("minishell (get_git_branch) - close");
	if (bytes_read == 0)
		return (NULL);
	branch[bytes_read] = '\0';
	git_str_replace(branch, bytes_read);
	if (ft_strncmp(branch, "ref: refs/heads/", 16) == 0)
		branch_name = ft_strdup(branch + 16);
	else
		branch_name = ft_strdup("(detached)");
	if (!branch_name)
		return (perror("minishell (get_git_branch) - malloc"), NULL);
	return (branch_name);
}
