/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:32:40 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/03 00:18:29 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

void	log_print(t_philo *philo, char *str)
{
	long	time_stamp;

	time_stamp = get_time() - philo->simulation_state->simulation_start;
	pthread_mutex_lock(&philo->simulation_state->logprint_lock);
	printf("%ld %d %s\n", time_stamp, philo->philo_id, str);
	pthread_mutex_unlock(&philo->simulation_state->logprint_lock);
}
