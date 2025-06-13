/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:46:39 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/03 01:13:41 by ihhadjal         ###   ########.fr       */
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
