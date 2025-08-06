/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:19:09 by anavagya          #+#    #+#             */
/*   Updated: 2025/08/06 13:45:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	timestamp = get_time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->somebody_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d %s\n", timestamp, philo->id + 1, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->data->death_mutex);
}

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (int)1000) + (time.tv_usec / 1000));
}

void	cleanup_philo(t_philo *philo)
{
	int	i;

	if (philo)
	{
		i = 0;
		while (i < philo->data->philo_num)
		{
			pthread_mutex_destroy(&philo[i].meal_lock);
			i++;
		}
	}
	if (philo)
		free(philo);
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	cleanup_philo(data->philo);
}
