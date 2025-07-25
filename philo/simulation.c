/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:25:20 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/25 15:47:58 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time_in_ms() < philo->data->start_time)
		usleep(50);
	if (philo->id % 2 == 0)
		usleep(500);
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
		philo_eat(philo);
		put_down_forks(philo, philo->data);
		philo_sleep(philo, philo->data->time_to_sleep);
		philo_think(philo, philo->data->time_to_die / 4);
	}
	return (NULL);
}
