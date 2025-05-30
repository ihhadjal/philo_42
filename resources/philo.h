/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:16:45 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/30 19:11:40 by ihhadjal         ###   ########.fr       */
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
# include <sys/time.h>
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
	long			simulation_start;
	pthread_mutex_t	logprint_lock;

}					t_simulation;

typedef struct s_fork
{
	pthread_mutex_t	fork_lock;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_t		thread_philo;
	t_arguments		*philo_arguments;
	t_simulation	*simulation_state;
	t_fork			*right_fork;
	t_fork			*left_fork;
}					t_philo;


int					parsing(int argc, char **argv);
int					check_input(char *argv);
int					my_atoi(const char *nptr);
int					my_isdigit(int c);
void				init_program_arguments(char **argv);
void	init_philo(t_arguments *arguments, t_simulation *simulation);
long	get_time(void);
void	*routine(void *arg);
void	lock_unlock(t_philo *philo);
#endif