/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:46:39 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/31 14:44:43 by ihhadjal         ###   ########.fr       */
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
			i++;
		}
		i = 0;
		while (i < philo->philo_arguments->nb_philo)
		{
			pthread_join(philo[i].thread_philo, NULL);
			i++;
		}
	}
	return (0);
}
void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// philo->simulation_state->death_flag = 1;
	while (check_death_flag(philo) == 0)
	{
		ft_usleep(philo->philo_arguments->time_sleep);
		log_print(philo, "is sleeping");
		log_print(philo, "is thinking");
	}
	return NULL;
}
int	check_death_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->simulation_state->death_flag_lock);
	if (philo->simulation_state->death_flag == 1)
		return (1);
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