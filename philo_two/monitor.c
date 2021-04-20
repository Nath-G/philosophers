/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:18:40 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/20 19:02:06 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_death(t_prog_dt *dt, t_philo_dt *phi, struct timeval cur_time,
				unsigned long int time_stamp)
{
	dt->is_finish = 1;
	dt->one_is_died = 1;
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / ONE_MLSEC), phi->name, " died\n", dt->log_lock);
	if (sem_post(dt->end_lock))
		return (1);
	return (0);
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
		
		if (sem_wait(data->finish_eaten))
			return (NULL);
		++i;
		if (i == data->n_philo && !data->one_is_died)
		{
			data->is_finish = 1;
			ft_get_time(&cur_time);
			time_stamp = ft_get_time_diff(&cur_time, data->time_start);
			ft_display_log((time_stamp / ONE_MLSEC), "all philos",
				" have eaten\n", data->log_lock);
			if (sem_post(data->end_lock))
				return (NULL);
		}
	}
	return (NULL);
}

void		*death_checker(void *data)
{
	int					i;
	t_philo_dt			*phi;
	unsigned long int	time_stamp;
	struct timeval		cur_time;
	t_prog_dt			*dt;

	i = 0;
	dt = (t_prog_dt *)data;
	phi = dt->philo;
	while (!dt->is_finish || !dt->is_finish)
	{
		if (sem_wait(phi->meal_time))
			return (NULL);
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, phi->time_last_meal);
		if ((time_stamp) > dt->time_to_die)
		{
			ft_death(dt, phi, cur_time, time_stamp);
			break ;
		}
		if (sem_post(phi->meal_time))
			return (NULL);
		usleep(10);
	}
	return (NULL);
}
