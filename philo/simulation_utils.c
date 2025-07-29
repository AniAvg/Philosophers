/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:55:43 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/29 18:08:29 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
		usleep(100);//200
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo, long ms)
{
	long	time;

	// time = get_time_in_ms();
	// while (get_time_in_ms() - time < ms)
	// 	usleep(100);
	print_status(philo, "is eating");
	pthread_mutex_lock(&(philo->meal_time_mutex));
	philo->last_meal = get_time_in_ms();
	philo->meal_count++;
	time = get_time_in_ms();
	pthread_mutex_unlock(&(philo->meal_time_mutex));
	while (get_time_in_ms() - time < ms)
		usleep(100);
}

void	put_down_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
}

void	philo_sleep(t_philo *philo, long ms)
{
	long	time;

	usleep(100);
	time = get_time_in_ms();
	print_status(philo, "is sleeping");
	while (get_time_in_ms() - time < ms)
		usleep(100);
}

void	philo_think(t_philo *philo)//, long ms)
{
	//long	time;
	//time = get_time_in_ms();
	print_status(philo, "is thinking");
	// while (get_time_in_ms() - time < ms)
	// 	usleep(100);
}
