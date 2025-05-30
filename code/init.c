/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:40:37 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/30 18:46:14 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

void	init_program_arguments(char **argv)
{
	t_arguments	*arguments;
	t_simulation *simulation_state;


	arguments = malloc(sizeof(t_arguments));
	simulation_state = malloc(sizeof(t_simulation));
	if (!simulation_state)
		return ;
	if (!arguments)
		return ;
	arguments->nb_philo = my_atoi(argv[1]);
	arguments->time_die = my_atoi(argv[2]);
	arguments->time_eat = my_atoi(argv[3]);
	arguments->time_sleep = my_atoi(argv[4]);
	simulation_state->death_flag = 0;
	pthread_mutex_init(&(simulation_state->death_flag_lock), NULL);
	pthread_mutex_init(&(simulation_state->logprint_lock), NULL);
	simulation_state->simulation_start = get_time();
	init_philo(arguments, simulation_state);
}

long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	init_philo(t_arguments *arguments, t_simulation *simulation)
{
	t_fork	*forks;
	t_philo *philo;
	int		i;

	i = 0;
	forks = malloc(arguments->nb_philo * sizeof(t_fork));
	philo = malloc(arguments->nb_philo * sizeof(arguments->nb_philo));
	if (!forks)
		return ;
	if (!philo)
		return ;
	while (i < arguments->nb_philo)
	{
		pthread_mutex_init(&(forks[i].fork_lock), NULL);
		philo[i].philo_id = i + 1;
		philo[i].philo_arguments = arguments;
		philo[i].simulation_state = simulation;
		philo[i].last_meal_time = simulation->simulation_start;
		philo[i].right_fork = &forks[i];
		philo[i].left_fork = &forks[(i - 1) % arguments->nb_philo];
		i++;
	}
}
