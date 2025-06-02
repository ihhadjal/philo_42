/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:28:46 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/03 00:18:15 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

void	check_times_eat(t_philo *philo)
{
	if (!philo->done_eating && philo->philo_arguments->x_philo_eats > 0
		&& philo->meals_eaten >= philo->philo_arguments->x_philo_eats)
	{
		pthread_mutex_lock(&philo->simulation_state->meal_lock);
		philo->simulation_state->finished_eating++;
		philo->done_eating = 1;
		pthread_mutex_unlock(&philo->simulation_state->meal_lock);
	}
}

void	sleeping(t_philo *philo)
{
	if (!check_death_flag(philo))
	{
		log_print(philo, "is sleeping");
		ft_usleep(philo->philo_arguments->time_sleep);
	}
}
