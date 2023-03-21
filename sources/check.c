/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:20:39 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/21 15:01:29 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_error(void)
{
	printf("Invalid parameters\n");
	return (0);
}

int	atoi_check(const char *str, int i)
{
	int	pos;
	int	res;

	res = 0;
	pos = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			pos *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = (res * 10) + str[i] - 48;
		if ((str[i + 1] <= '9' && str[i + 1] >= '0') && (res > 214748364))
			return (1);
		if (res == 214748364)
			if ((pos == 1 && str[i + 1] == '8') || str[i + 1] == '9')
				return (1);
		i++;
	}
	return (0);
}

int	check_max_ints(char **av)
{
	int		i;
	int		j;
	int		sign;

	i = 1;
	while (av[i])
	{
		sign = 0;
		j = 0;
		while (av[i][j])
		{
			if (sign++ == 0)
				if (atoi_check(av[i], j) == 1)
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_ints(char **av)
{
	int	i;
	int	j;
	int	sign;

	i = 1;
	while (av[i])
	{
		sign = 0;
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] == '+' || av[i][j] == '-') && sign == 0)
				j++;
			if (av[i][j] > '9' || av[i][j] < '0')
				return (1);
			if (ft_atoi(av[i]) < 1)
				return (1);
			j++;
			sign++;
		}
		i++;
	}
	return (0);
}
