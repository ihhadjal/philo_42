/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:50:02 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/03 00:19:04 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

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

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	cleanup(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_arguments->nb_philo)
		pthread_mutex_destroy(&philo[i++].right_fork->fork_lock);
	pthread_mutex_destroy(&philo->simulation_state->death_flag_lock);
	pthread_mutex_destroy(&philo->simulation_state->meal_lock);
	pthread_mutex_destroy(&philo->simulation_state->logprint_lock);
	free(philo->philo_arguments);
	free(philo->simulation_state);
	free(philo);
}

int	check_death_flag(t_philo *philo)
{
	int	should_end;

	pthread_mutex_lock(&philo->simulation_state->death_flag_lock);
	should_end = philo->simulation_state->death_flag;
	pthread_mutex_unlock(&philo->simulation_state->death_flag_lock);
	return (should_end);
}
