/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:50:02 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/28 17:04:26 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

int	check_input(char *argv, int num)
{
	int	i;

	i = 0;
	if (num <= 0)
		return (printf("all arguments must be higher than zero\n"), 1);
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (printf("only numbers are accepted\n"), 1);
		i++;
	}
	return (0);
}
