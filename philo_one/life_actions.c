/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:33 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/08 12:29:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	checking_time_ate(t_philo_dt *phi, t_prog_dt *dt)
{
	unsigned long int	time_stamp;
	struct timeval cur_time;

	if(ft_get_time(&cur_time))
		return(1);
	time_stamp = ft_get_time_diff(&cur_time, phi->time_last_meal);
	if ( (time_stamp/1000) > phi->time_to_die)
	{
		pthread_mutex_lock(&dt->died);
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, phi->time_start);
		ft_display_log((time_stamp / 1000), phi->name, " dead\n");
		phi->is_dead = 1;
		pthread_mutex_unlock(&dt->died);
		return (1);
	}
	return (0);
}

static void	take_forks(t_philo_dt *phi, t_prog_dt *dt)
{
	long unsigned int	time_stamp;
	struct timeval		cur_time;
	(void)dt; // modifier take forks avec une seule valeur
	pthread_mutex_lock(&phi->left_fork);
	pthread_mutex_lock(phi->right_fork);
	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, phi->time_start);
	ft_display_log((time_stamp / 1000), phi->name, " has taken a fork\n");
	ft_display_log((time_stamp / 1000), phi->name, " has taken a fork\n");
}

int		philo_eats(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;
//dt a enlever si inutile dnas fork
	if (checking_time_ate(phi, dt))
		return (1);
	take_forks(phi, dt);
	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, phi->time_start);
	ft_display_log((time_stamp / 1000), phi->name, " is eating\n");
	usleep(phi->time_to_eat * ONE_MILLISEC);
	pthread_mutex_lock(&phi->meals);
	phi->meals_ate++;
	pthread_mutex_unlock(&phi->meals);
	ft_get_time(phi->time_last_meal);
	pthread_mutex_unlock(&phi->left_fork);
	pthread_mutex_unlock(phi->right_fork);
	return (0);
}

int		philo_sleeps(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;
(void)dt;//a enlver si inutile

	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, phi->time_start);
	ft_display_log((time_stamp / 1000), phi->name, " is sleeping\n");
	usleep(phi->time_to_sleep * ONE_MILLISEC);
	return (0);
}

int		philo_thinks(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

(void)dt;//enlever dt si inutile
	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, phi->time_start);
	{
		ft_display_log((time_stamp / 1000), phi->name, " is thinking\n");
		usleep(1000);
	}
//	printf("ok dans philo_thinks phi = %s\n", phi->name);
	return (0);
}
