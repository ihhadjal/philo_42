/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:33:49 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/02 23:57:51 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

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
