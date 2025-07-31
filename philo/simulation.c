/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:25:20 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/31 18:38:07 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time_in_ms() < philo->data->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->somebody_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		pick_up_forks(philo, philo->data);
		philo_eat(philo, philo->data->time_to_eat);
		put_down_forks(philo, philo->data);
		if (philo->data->must_eat_count > 0
			&& philo->meal_count >= philo->data->must_eat_count)
		{
			pthread_mutex_lock(&philo->meal_time_mutex);
			philo->data->diner_is_over = 1;
			pthread_mutex_unlock(&philo->meal_time_mutex);
			break ;
		}
		philo_sleep(philo, philo->data->time_to_sleep);
		philo_think(philo, 1);
	}
	return (NULL);
}
