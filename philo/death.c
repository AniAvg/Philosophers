/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:39:53 by anavagya          #+#    #+#             */
/*   Updated: 2025/08/14 15:39:02 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_data *data, long time, int i)
{
	if (time > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->somebody_died)
		{
			data->somebody_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", get_time_in_ms()
				- data->start_time, data->philo[i].id + 1);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_unlock(&data->philo[i].meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&data->philo[i].meal_lock);
		return (1);
	}
	return (0);
}

int	is_meal_limit_reached(t_data *data, int i)
{
	pthread_mutex_lock(&(data->philo[i].meal_lock));
	if (data->philo[i].meal_count == data->must_eat_count)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->diner_is_over = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&(data->philo[i].meal_lock));
		return (1);
	}
	pthread_mutex_unlock(&(data->philo[i].meal_lock));
	return (0);
}

void	*if_sb_is_dead(void *arg)
{
	int		i;
	long	time;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		usleep(100);
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&data->philo[i].meal_lock);
			time = get_time_in_ms() - data->philo[i].last_meal;
			if (check_philo_death(data, time, i))
				return (NULL);
			pthread_mutex_unlock(&data->philo[i].meal_lock);
			if (is_meal_limit_reached(data, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
