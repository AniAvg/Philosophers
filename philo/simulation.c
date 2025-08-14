/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:25:20 by anavagya          #+#    #+#             */
/*   Updated: 2025/08/14 15:35:49 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->somebody_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

int	check_meal_count(t_philo *philo, int meal_count)
{
	if (philo->data->must_eat_count > 0
		&& meal_count >= philo->data->must_eat_count)
	{
		pthread_mutex_lock(&(philo->data->death_mutex));
		philo->data->diner_is_over = 1;
		pthread_mutex_unlock(&(philo->data->death_mutex));
		return (1);
	}
	return (0);
}

void	eating(t_philo *philo)
{
	pick_up_forks(philo, philo->data);
	philo_eat(philo, philo->data->time_to_eat);
	put_down_forks(philo, philo->data);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	int		meal_count;

	philo = (t_philo *)arg;
	while (get_time_in_ms() < philo->data->start_time)
		usleep(50);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		if (philo->data->philo_num == 1)
			return (one_philo(philo));
		eating(philo);
		pthread_mutex_lock(&(philo->meal_lock));
		meal_count = philo->meal_count;
		pthread_mutex_unlock(&(philo->meal_lock));
		if (check_meal_count(philo, meal_count))
			return (NULL);
		philo_sleep(philo, philo->data->time_to_sleep);
		philo_think(philo, 1);
	}
	return (NULL);
}
