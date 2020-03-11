/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:56:02 by kradoste          #+#    #+#             */
/*   Updated: 2019/06/05 18:04:58 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_vars
{
	int		co;
	int		key;
	int		qui;
	int		re;
	int		std;
	int		string;
	int		print;
	int		hash;
	char	*str;
}				t_vars;

int				swap_end(int n);
void			run_prog(int x, char *str);
void			handle_errors(int ac, char **argv, t_vars *all);
int				flags(t_vars *all, char *str);
char			*read_input(void);
char			*crypto_string(int x);
int				file_checker(t_vars *all, char *str);
void			hash_algorithm(t_vars *all, char *str);
void			next_arg2(t_vars *all, char *str);
void			next_arg(t_vars *all, char *str);

#endif
