/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:56:33 by kradoste          #+#    #+#             */
/*   Updated: 2019/05/01 18:03:52 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	run_prog(int x, char *str)
{
	if (x == 1)
		ft_md5((unsigned char *)str);
	if (x == 2)
		ft_sha256((unsigned char *)str);
}

char	*crypto_string(int x)
{
	if (x == 1)
		return ("md5");
	else if (x == 2)
		return ("sha256");
	return (NULL);
}

int		flags(t_vars *all, char *str)
{
	if (all->key && ft_strcmp(str, "-r") == 0)
		all->re = 1;
	else if (all->key && ft_strcmp(str, "-p") == 0)
		all->std = 1;
	else if (all->key && ft_strcmp(str, "-q") == 0)
		all->qui = 1;
	else if (all->key && ft_strcmp(str, "-s") == 0)
		all->string = 1;
	else
		return (0);
	all->co++;
	return (1);
}

void	handle_errors(int ac, char **argv, t_vars *all)
{
	if (ac == 1)
	{
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		exit(0);
	}
	if (!ft_strcmp("md5", argv[1]))
		all->hash = 1;
	else if (!ft_strcmp("sha256", argv[1]))
		all->hash = 2;
	else if (all->hash == 0)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", argv[1]);
		exit(0);
	}
}

int		file_checker(t_vars *all, char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl %s: %s: No such file or directory\n",
crypto_string(all->hash), str);
		all->co++;
		return (0);
	}
	return (1);
}
