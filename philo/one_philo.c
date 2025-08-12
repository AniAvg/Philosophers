/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:26:48 by anavagya          #+#    #+#             */
/*   Updated: 2025/08/12 13:27:16 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(t_philo *philo)
{
	philo->data->start_time = get_time_in_ms();
	pthread_mutex_lock(&(philo->meal_lock));
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&(philo->meal_lock));
	pthread_mutex_lock(&(philo->data->forks[0]));
	pthread_mutex_lock(&(philo->data->print_mutex));
	printf("%ld %d has taken a fork\n",
		get_time_in_ms() - philo->data->start_time, philo[0].id + 1);
	pthread_mutex_unlock(&(philo->data->print_mutex));
	pthread_mutex_unlock(&(philo->data->forks[0]));
	pthread_mutex_lock(&(philo->data->death_mutex));
	if (philo->data->somebody_died)
	{
		pthread_mutex_unlock(&(philo->data->death_mutex));
		return (NULL);
	}
	pthread_mutex_unlock(&(philo->data->death_mutex));
	return (NULL);
}
