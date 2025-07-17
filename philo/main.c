/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:34:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/17 17:59:11 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_philo *philo, t_data *data, char **argv)
{
	int	i;

	philo->thread = malloc(sizeof(pthread_t) * data->philo_num);
	if (!philo->thread)
		return ;
	philo->data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!philo->data->forks)
		return ;
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&(data->forks), NULL) != 0)
			return ;
	}
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		return ;
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = 0;
}

void	pick_up_forks(t_philo *philo, t_data *data)
{
	philo->left_fork = philo->id;
	if (philo->id == (data->philo_num - 1))
		philo->right_fork = 0;
	else
		philo->right_fork = philo->id + 1;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	print_status(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->meal_time_mutex));
	philo->last_meal = get_time_in_ms();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->meal_time_mutex));
	print_status(philo->data, "is eating");
}

void	put_down_forks(t_philo *philo, t_data *data, long ms)
{
	long	time;

	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	print_status(philo, "puts down forks");
	time = get_time_in_ms();
	while (get_time_in_ms() - time < ms)
		usleep(100);
}

void	philo_sleep(t_philo *philo, long ms)
{
	long	time;

	time = get_time_in_ms();
	print_status(philo, "is sleeping");
	while (get_time_in_ms() - time < ms)
		usleep(100);
}

void	philo_think(t_philo *philo, long ms)
{
	long	time;

	print_status(philo, "is thinking");
	time = get_time_in_ms();
	while (get_time_in_ms() - time < ms)
		usleep(100);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pick_up_forks(philo, data);
		philo_eat(philo);
		put_down_forks(philo, data);
		philo_sleep(philo, ms);
		philo_think(philo, ms);
	}
}

void	creating_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms() + 100;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philo, NULL, philosopher, NULL) != 0)
			return ;
		if (pthread_join(data->philo, NULL) != 0)
			return ;
		i++;
	}
}

int	main(int argc, char *argv)
{
	t_data	*data;
	t_philo	*philo;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!validation(argc, argv))
		return (1);
	init(philo, data, argv);
	creating_threads(data);
	return (0);
}
