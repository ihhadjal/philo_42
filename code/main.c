/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:46:39 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/31 16:05:34 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = NULL;
	if (parsing(argc, argv) == 0)
	{
		init_program_arguments(argv, &philo);
		while (i < philo->philo_arguments->nb_philo)
		{
			pthread_create(&philo[i].thread_philo, NULL, routine, &philo[i]);
			// pthread_create(&philo[i].thread_monitor, NULL, monitor, &philo[i]);
			i++;
		}
		i = 0;
		while (i < philo->philo_arguments->nb_philo)
		{
			pthread_join(philo[i].thread_philo, NULL);
			// pthread_join(philo[i].thread_monitor, NULL);
			i++;
		}
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo *monitor;

	monitor = (t_philo *)arg;
	while (1)
	{
		if (monitor->philo_arguments->time_die > monitor->last_meal_time)
		{
			monitor->simulation_state->death_flag = !monitor->simulation_state->death_flag;
			break;
		}
	}
	return NULL;
}
void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (check_death_flag(philo) == 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork_lock);
		pthread_mutex_lock(&philo->left_fork->fork_lock);
		log_print(philo, "has taken a fork");
		log_print(philo, "has taken a fork");
		log_print(philo, "is eating");
		usleep(philo->philo_arguments->time_eat * 1000);
		pthread_mutex_unlock(&philo->right_fork->fork_lock);
		pthread_mutex_unlock(&philo->left_fork->fork_lock);
		log_print(philo, "is sleeping");
		usleep(philo->philo_arguments->time_sleep * 1000);
		log_print(philo, "is thinking");
		if (monitoring(philo) == 1)
		{
			log_print(philo, "is dead");
			break;
		}
	}
	return NULL;
}
int	monitoring(t_philo *philo)
{
	if ((get_time() - philo->last_meal_time) > philo->philo_arguments->time_die)
	{
		philo->simulation_state->death_flag = !philo->simulation_state->death_flag;
		return 1;
	}
	return 0;	
}

int	check_death_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->simulation_state->death_flag_lock);
	if (philo->simulation_state->death_flag == 1)
	{
		log_print(philo, "has died");
		return (1);
	}
	pthread_mutex_unlock(&philo->simulation_state->death_flag_lock);
	return (0);
}

void log_print(t_philo *philo, char *str)
{
	long	time_stamp;

	time_stamp = get_time() - philo->simulation_state->simulation_start;
	pthread_mutex_lock(&philo->simulation_state->logprint_lock);
	printf("%ld %d %s\n",time_stamp , philo->philo_id, str);
	pthread_mutex_unlock(&philo->simulation_state->logprint_lock);
}
