/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:33:49 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/03 01:13:58 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

void	*monitoring(void *arg)
{
	t_philo	*philo;
	long	time_since_last_meal;
	int		i;
	int		nb_philo;

	philo = (t_philo *)arg;
	nb_philo = philo->philo_arguments->nb_philo;
	while (1)
	{
		i = 0;
		while (i < philo->philo_arguments->nb_philo)
		{
			pthread_mutex_lock(&philo[i].simulation_state->meal_lock);
			time_since_last_meal = get_time() - philo[i].last_meal_time;
			pthread_mutex_unlock(&philo[i].simulation_state->meal_lock);
			if (time_since_last_meal > philo[i].philo_arguments->time_die)
			{
				check_if_dead(philo, i);
				return (NULL);
			}
			i++;
		}
		check_if_finished(philo, nb_philo);
	}
	return (NULL);
}

void	*check_if_finished(t_philo *philo, int nb_philo)
{
	int	finished;

	if (philo->philo_arguments->x_philo_eats > 0)
	{
		pthread_mutex_lock(&philo->simulation_state->meal_lock);
		finished = philo->simulation_state->finished_eating;
		pthread_mutex_unlock(&philo->simulation_state->meal_lock);
		if (finished >= nb_philo)
		{
			pthread_mutex_lock(&philo->simulation_state->death_flag_lock);
			philo->simulation_state->death_flag = 1;
			pthread_mutex_unlock(&philo->simulation_state->death_flag_lock);
			return (NULL);
		}
	}
	usleep(1000);
	return (NULL);
}

void	check_if_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].simulation_state->death_flag_lock);
	if (!philo[i].simulation_state->death_flag)
	{
		philo[i].simulation_state->death_flag = 1;
		pthread_mutex_unlock(&philo[i].simulation_state->death_flag_lock);
		log_print(&philo[i], "has died");
	}
	else
		pthread_mutex_unlock(&philo[i].simulation_state->death_flag_lock);
}
