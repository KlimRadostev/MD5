/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:01:28 by kradoste          #+#    #+#             */
/*   Updated: 2019/06/05 18:04:43 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_input(void)
{
	char	*str;
	char	*ch;

	ch = ft_strnew(1);
	str = ft_strnew(0);
	while (read(0, ch, 1))
	{
		str = str_append(str, ch, 1, 1);
		ch = ft_strnew(1);
	}
	free(ch);
	return (str);
}

void	hash_algorithm(t_vars *all, char *str)
{
	int		fd;
	char	*buf;
	char	*tmp;

	if (all->string)
	{
		all->string = 0;
		run_prog(all->hash, str);
		if (all->qui || !all->re)
			ft_printf("\n");
		return ;
	}
	fd = open(str, O_RDONLY);
	buf = ft_strnew(1);
	tmp = ft_strnew(0);
	while (read(fd, buf, 1))
	{
		tmp = str_append(tmp, buf, 1, 1);
		buf = ft_strnew(1);
	}
	run_prog(all->hash, tmp);
	free(tmp);
	free(buf);
	if (all->qui || !all->re)
		ft_printf("\n");
}

void	next_arg2(t_vars *all, char *str)
{
	if (all->re)
	{
		if (!all->string && file_checker(all, str) == 0)
			return ;
		if (!all->string)
		{
			hash_algorithm(all, str);
			ft_printf(" \"%s\"\n", str);
		}
		else
		{
			hash_algorithm(all, str);
			ft_printf(" %s\n", str);
		}
		all->co++;
		return ;
	}
	if (!all->string && file_checker(all, str) == 0)
		return ;
	if (all->string)
		ft_printf("%s (\"%s\") = ", crypto_string(all->hash), str);
	else
		ft_printf("%s (%s) = ", crypto_string(all->hash), str);
	hash_algorithm(all, str);
	all->co++;
}

void	next_arg(t_vars *all, char *str)
{
	if (!all->string && all->key && flags(all, str) == 1)
		return ;
	all->key = 0;
	all->print = 1;
	if (all->std)
	{
		str = read_input();
		ft_printf("%s", str);
		run_prog(all->hash, str);
		free(str);
		all->std = 0;
		ft_printf("\n");
		return ;
	}
	if (all->qui)
	{
		if (!all->string && file_checker(all, str) == 0)
			return ;
		hash_algorithm(all, str);
		all->co++;
		return ;
	}
	next_arg2(all, str);
}

int		main(int ac, char **argv)
{
	char	*str;
	t_vars	all;

	all.co = 2;
	all.key = 1;
	all.qui = 0;
	all.re = 0;
	all.std = 0;
	all.string = 0;
	all.print = 0;
	all.hash = 0;
	handle_errors(ac, argv, &all);
	while (all.co < ac)
		next_arg(&all, argv[all.co]);
	if (all.print == 0)
	{
		str = read_input();
		if (all.std)
			ft_printf("%s", str);
		run_prog(all.hash, str);
		free(str);
		ft_printf("\n");
	}
	return (0);
}
