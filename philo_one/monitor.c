/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:18:40 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/04 11:33:25 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_death(t_prog_dt *dt, t_philo_dt *phi, struct timeval cur_time,
				unsigned long int time_stamp)
{
	dt->one_is_died = 1;
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / ONE_MLSEC), phi->name, " died\n",
		dt);
	dt->is_finish = 1;
	pthread_mutex_unlock(&dt->finish_lock);
	pthread_mutex_unlock(&(phi->meal_time));
}

void		*eats_checker(void *data_philo)
{
	int					i;
	t_prog_dt			*data;
	struct timeval		cur_time;
	unsigned long int	time_stamp;

	data = (t_prog_dt *)data_philo;
	i = 0;
	while (i < data->n_philo && !data->is_finish)
	{
		pthread_mutex_lock(&data->philo[i].finish_eaten);
		++i;
		if (i == data->n_philo && !data->one_is_died)
		{
			ft_get_time(&cur_time);
			time_stamp = ft_get_time_diff(&cur_time, data->time_start);
			ft_display_log((time_stamp / ONE_MLSEC), "all philos",
				" have eaten\n", data);
			data->is_finish = 1;
			pthread_mutex_unlock(&data->finish_lock);
		}
	}
	return (NULL);
}

void		*death_checker(void *data)
{
	unsigned long int	time_stamp;
	struct timeval		cur_time;
	t_prog_dt			*dt;
	int					i;

	dt = (t_prog_dt *)data;
	i = -1;
	while (!dt->is_finish && (++i < dt->n_philo))
	{
		pthread_mutex_lock(&(dt->philo[i].meal_time));
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, dt->philo[i].time_last_meal);
		if (time_stamp > dt->time_to_die)
		{
			ft_death(dt, &(dt->philo[i]), cur_time, time_stamp);
			break ;
		}
		pthread_mutex_unlock(&(dt->philo[i].meal_time));
		usleep(1);
		if (i == (dt->n_philo - 1))
			i = -1;
	}
	return (NULL);
}
