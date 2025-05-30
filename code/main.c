/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:46:39 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/30 13:22:06 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

int main(int argc, char **argv)
{
	if (argc && argv)
		parsing(argc, argv);
	init_program_arguments(argv);
	return (0);
}

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
	
}
