/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:13:18 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/31 14:02:27 by ihhadjal         ###   ########.fr       */
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
		if (check_input(argv[i]) == 0)
		{
			if (num <= 0)
			{
				return (printf("error: all arguments must be higher than zero\n"),
					1);
			}
		}
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
			return (1);
		}
		i++;
	}
	return (0);
}
