/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 13:16:42 by jponcele          #+#    #+#             */
/*   Updated: 2014/05/02 14:39:21 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_script.h>

char							*get_shell(char **env)
{
	char						*shell;

	shell = check_cmd(env, ft_getenv(env, "SHELL"));
	return ((shell) ? shell : "/bin/sh");
}

char							*ft_getenv(char **env, char *name)
{
	int							i;
	char						**split_value;

	name = ft_strjoin(name, "=");
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			split_value = ft_strsplit(env[i], "=");
			return (split_value[1]);
		}
		i++;
	}
	return (NULL);
}

char							*check_cmd(char **env, char *cmd)
{
	char						**paths;
	char						*path;
	int							i;

	path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_strsplit(path, ":");
	i = 0;
	while (paths[i])
	{
		path = ft_strdup(cmd);
		if (!ft_strstr(path, "/"))
			path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(path, X_OK) >= 0 && !ft_strequ(path, "./42sh"))
			return (path);
		i++;
	}
	return (NULL);
}
