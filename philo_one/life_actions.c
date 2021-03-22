/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:27:33 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/22 17:12:55 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	take_forks(t_philo_dt *phi, t_prog_dt *dt)
{
	long unsigned int	time_stamp;
	struct timeval		cur_time;

	pthread_mutex_lock(&phi->left_fork);
	pthread_mutex_lock(phi->right_fork);
	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / 1000), phi->name, " has taken a fork\n");
	ft_display_log((time_stamp / 1000), phi->name, " has taken a fork\n");
}

int		philo_eats(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	pthread_mutex_lock(&phi->meal_time);
	ft_get_time(phi->time_last_meal);
	pthread_mutex_unlock(&phi->meal_time);
	take_forks(phi, dt);
	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / 1000), phi->name, " is eating\n");
	usleep(dt->time_to_eat * ONE_MILLISEC);
	phi->meals_ate++;
	if (phi->meals_ate >= dt->n_meals)
		pthread_mutex_unlock(&phi->finish_eaten);
	pthread_mutex_unlock(&phi->left_fork);
	pthread_mutex_unlock(phi->right_fork);
	return (0);
}

int		philo_sleeps(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / 1000), phi->name, " is sleeping\n");
	usleep(dt->time_to_sleep * ONE_MILLISEC);
	return (0);
}

int		philo_thinks(t_philo_dt *phi, t_prog_dt *dt)
{
	struct timeval	cur_time;
	long unsigned	time_stamp;

	ft_get_time(&cur_time);
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	{
		ft_display_log((time_stamp / 1000), phi->name, " is thinking\n");
		usleep(1000);
	}
	return (0);
}
