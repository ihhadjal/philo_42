/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:16:45 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/30 13:16:27 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/header/ft_printf.h"
# include "libft/header/get_next_line.h"
# include "libft/header/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_arguments
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
}					t_arguments;

typedef struct s_simulation
{
	int				death_flag;
	pthread_mutex_t	death_flag_lock;
	long long		simulation_start;
	pthread_mutex_t	logprint_lock;

}					t_simulation;

typedef struct s_fork
{
	pthread_mutex_t	fork_lock;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_philo;
	t_arguments		*philo_arguments;
	t_fork			*right_fork;
	t_fork			*left_fork;
	long long		last_meal_time;
	int				meals_eaten;
	t_simulation	*simulation_state;
}					t_philo;

int					parsing(int argc, char **argv);
int					check_input(char *argv);
int					my_atoi(const char *nptr);
int					my_isdigit(int c);
void	init_program_arguments(char **argv);
#endif