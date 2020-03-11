/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:01:36 by kradoste          #+#    #+#             */
/*   Updated: 2019/05/01 17:43:23 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	g_q[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

unsigned int	g_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5,
	9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11,
	16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

int				find_length(unsigned char *str)
{
	int	l;
	int	len;

	l = ft_strlen((char *)str);
	len = ((l + 8) / 64) * 64 + 64;
	return (len);
}

static void		md5_initialize(unsigned char *str, t_md5 *t)
{
	int	i;

	t->a0 = 0x67452301;
	t->b0 = 0xefcdab89;
	t->c0 = 0x98badcfe;
	t->d0 = 0x10325476;
	t->out_len = find_length(str);
	t->out = (unsigned char *)ft_strnew(t->out_len);
	ft_strcpy((char *)t->out, (char *)str);
	t->len = ft_strlen((char *)str) * 8;
	t->out[ft_strlen((char *)str)] = 1 << 7;
	i = 0;
	while (i < 8)
	{
		t->out[t->out_len - 8 + i] = ((char *)&(t->len))[i];
		i++;
	}
}

static void		md5_set_var(t_md5 *t, int i)
{
	t->x = 0;
	while (t->x < 16)
	{
		t->var[t->x] = 0;
		t->var[t->x] += t->out[i * 64 + t->x * 4 + 0];
		t->var[t->x] += t->out[i * 64 + t->x * 4 + 1] << 8;
		t->var[t->x] += t->out[i * 64 + t->x * 4 + 2] << 16;
		t->var[t->x] += t->out[i * 64 + t->x * 4 + 3] << 24;
		t->x++;
	}
	t->a = t->a0;
	t->b = t->b0;
	t->c = t->c0;
	t->d = t->d0;
}

static void		md5_mainloop(t_md5 *t, int j)
{
	if (j < 16)
	{
		t->f = (t->b & t->c) | ((~t->b) & t->d);
		t->g = j;
	}
	else if (j < 32)
	{
		t->f = (t->d & t->b) | ((~t->d) & t->c);
		t->g = (5 * j + 1) & 15;
	}
	else if (j < 48)
	{
		t->f = t->b ^ t->c ^ t->d;
		t->g = (3 * j + 5) & 15;
	}
	else
	{
		t->f = t->c ^ (t->b | (~t->d));
		t->g = (7 * j) & 15;
	}
	t->f = t->f + t->a + g_q[j] + t->var[t->g];
	t->a = t->d;
	t->d = t->c;
	t->c = t->b;
	t->b += ((t->f << g_s[j]) | (t->f >> (32 - g_s[j])));
}

void			ft_md5(unsigned char *str)
{
	t_md5			t;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	md5_initialize(str, &t);
	while (i < (t.out_len * 8) / 512)
	{
		md5_set_var(&t, i);
		j = -1;
		while (++j < 64)
			md5_mainloop(&t, j);
		t.a0 += t.a;
		t.b0 += t.b;
		t.c0 += t.c;
		t.d0 += t.d;
		i++;
	}
	t.a0 = swap_end(t.a0);
	t.b0 = swap_end(t.b0);
	t.c0 = swap_end(t.c0);
	t.d0 = swap_end(t.d0);
	ft_printf("%.8x%.8x%.8x%.8x", t.a0, t.b0, t.c0, t.d0);
	free(t.out);
}
