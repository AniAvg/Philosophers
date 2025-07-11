/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:36:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/11 16:58:47 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_die;
	int		start_time;
	int		eat_count;
	t_philo	*philo;

}	t_data;


// validation.c
int		ft_strlen(char * str);
int		ft_atoi(const char *str);
char	*validation(int argc, char *argv);

// main.c
#endif
