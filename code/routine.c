/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:11:55 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/03 01:16:43 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	one_philo_logic(philo);
	if (philo->philo_id % 2 == 0)
		ft_usleep(100);
	while (!check_death_flag(philo))
	{
		log_print(philo, "is thinking");
		if (philo->philo_id % 2 == 0)
		{
			if (left_fork_logic(philo) == 1)
				break ;
		}
		else
		{
			if (right_fork_logic(philo) == 1)
				break ;
		}
		eating_logic(philo);
		check_times_eat(philo);
		sleeping(philo);
	}
	return (NULL);
}

int	left_fork_logic(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_lock);
	if (check_death_flag(philo))
	{
		pthread_mutex_unlock(&philo->left_fork->fork_lock);
		return (1);
	}
	log_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->fork_lock);
	if (check_death_flag(philo))
	{
		pthread_mutex_unlock(&philo->right_fork->fork_lock);
		pthread_mutex_unlock(&philo->left_fork->fork_lock);
		return (1);
	}
	log_print(philo, "has taken a fork");
	return (0);
}

int	right_fork_logic(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_lock);
	if (check_death_flag(philo))
	{
		pthread_mutex_unlock(&philo->right_fork->fork_lock);
		return (1);
	}
	log_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork->fork_lock);
	if (check_death_flag(philo))
	{
		pthread_mutex_unlock(&philo->left_fork->fork_lock);
		pthread_mutex_unlock(&philo->right_fork->fork_lock);
		return (1);
	}
	log_print(philo, "has taken a fork");
	return (0);
}

int	one_philo_logic(t_philo *philo)
{
	if (philo->philo_arguments->nb_philo == 1)
	{
		log_print(philo, "is thinking");
		pthread_mutex_lock(&philo->right_fork->fork_lock);
		log_print(philo, "has taken a fork");
		ft_usleep(philo->philo_arguments->time_die + 10);
		pthread_mutex_unlock(&philo->right_fork->fork_lock);
		return (1);
	}
	return (0);
}

void	eating_logic(t_philo *philo)
{
	log_print(philo, "is eating");
	pthread_mutex_lock(&philo->simulation_state->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->simulation_state->meal_lock);
	ft_usleep(philo->philo_arguments->time_eat);
	pthread_mutex_unlock(&philo->left_fork->fork_lock);
	pthread_mutex_unlock(&philo->right_fork->fork_lock);
}
