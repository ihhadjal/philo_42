/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:46:39 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/03 00:14:23 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	monitoring_thread;
	int			i;

	i = 0;
	philo = NULL;
	if (parsing(argc, argv) == 0)
	{
		init_program_arguments(argv, &philo);
		while (i < philo->philo_arguments->nb_philo)
		{
			pthread_create(&philo[i].thread_philo, NULL, routine, &philo[i]);
			i++;
		}
		pthread_create(&monitoring_thread, NULL, monitoring, philo);
		pthread_join(monitoring_thread, NULL);
		i = 0;
		while (i < philo->philo_arguments->nb_philo)
		{
			pthread_join(philo[i].thread_philo, NULL);
			i++;
		}
		cleanup(philo);
	}
	return (0);
}

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
