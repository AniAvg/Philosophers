/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:34:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/08/01 12:16:40 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*if_sb_is_dead(void *arg)
{
	int		i;
	long	time;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&data->philo[i].meal_time_mutex);
			time = get_time_in_ms() - data->philo[i].last_meal;
			if (time > data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				if (!data->somebody_died)
				{
					data->somebody_died = 1;
					pthread_mutex_unlock(&data->death_mutex);
					pthread_mutex_lock(&data->print_mutex);
					printf("%ld %d died\n", get_time_in_ms() - data->start_time, data->philo[i].id + 1);
					pthread_mutex_unlock(&data->print_mutex);
					pthread_mutex_unlock(&data->philo[i].meal_time_mutex);
					return (NULL);
				}
				// else
				// 	pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_unlock(&data->philo[i].meal_time_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].meal_time_mutex);
			i++;
		}
		if (data->philo->meal_count == data->must_eat_count)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->diner_is_over = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

void	creating_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms() + 100;
	while (i < data->philo_num)
	{
		data->philo[i].last_meal = data->start_time;
		if (pthread_create(&data->philo[i].thread, NULL, philosopher, &data->philo[i]) != 0)
		{
			printf("Error creating thread %d\n", i);
			return ;
		}
		i++;
	}
	if (pthread_create(&data->philo_is_dead, NULL, if_sb_is_dead, data) != 0)
	{
		printf("Error creating death thread\n");
		return ;
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			printf("Error joining thread %d\n", i);
			return ;
		}
		i++;
	}
	if (pthread_join(data->philo_is_dead, NULL) != 0)
	{
		printf("Error creating death thread\n");
		return ;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!validation(argc, argv))
	{
		free(data->philo);
		free(data);
		write(2, "Error\n", 6);
		return (1);
	}
	init(data, argv);
	creating_threads(data);
	cleanup(data);
	free(data);
	return (0);
}
