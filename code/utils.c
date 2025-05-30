/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:50:02 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/30 11:51:24 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

int	parsing(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	if (argc < 5 || argc > 5)
		return (printf("error: the ammount of arguments is not right\n"), 1);
	while (argv[i])
	{
		num = my_atoi(argv[i]);
		check_input(argv[i]);
		if (num <= 0)
			return (printf("error: all arguments must be higher than zero\n"),
				1);
		i++;
	}
	return (0);
}

int	check_input(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!my_isdigit(argv[i]))
		{
			printf("error: only numbers are accepted\n");
			exit(1);
		}
		i++;
	}
	return (0);
}

int	my_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

int	my_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
