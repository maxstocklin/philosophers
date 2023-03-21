/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:50:35 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/21 14:57:19 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s_cpy;

	s_cpy = (char *) s;
	while (*s_cpy)
	{
		if (*s_cpy == (char) c)
			return (s_cpy);
		s_cpy++;
	}
	if (*s_cpy == (char) c)
		return (s_cpy);
	return (NULL);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *s)
{
	int		result;
	int		sign;
	char	*s_cpy;

	result = 0;
	sign = 1;
	s_cpy = (char *) s;
	if (ft_strlen(s_cpy) == 0)
		return (0);
	while (ft_strchr("\t\n\r\v\f ", *s_cpy))
		s_cpy++;
	if (*s_cpy == '+' && ft_isdigit(*(s_cpy + 1)))
		s_cpy++;
	if (*s_cpy == '-')
	{
		sign = -1;
		s_cpy++;
	}
	while (*s_cpy && ft_isdigit(*s_cpy))
		result = result * 10 + *s_cpy++ - '0';
	return (result * sign);
}
