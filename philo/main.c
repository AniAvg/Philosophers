/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:34:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/12 17:42:05 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_philo *philo, t_data *data, char **argv)
{
	philo->thread = malloc(sizeof(pthread_t) * data->philo_num);
	if (!philo->thread)
		return ;
	philo->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!philo->forks)
		return ;
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat_count = ft_atoi(argv[5]);
}

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pick_up_forks(philo);
		philo_eat();
		put_down_forks(philo);
		philo_sleep();
		philo_think();
	}
}

void	creating_threads(t_philo philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&philo, NULL, philosopher, NULL) != 0)
			return ;
		if (pthread_join(philo, NULL) != 0)
			return ;
		i++;
	}
}

int	main(int argc, char *argv)
{
	t_data	*data;
	t_philo	*philo;

	if (!validation(argc, argv))
		return (1);
	init(philo, data, argv);
	return (0);
}
