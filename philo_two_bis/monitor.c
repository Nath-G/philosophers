/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:18:40 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/03 11:33:41 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_death(t_prog_dt *dt, t_philo_dt *phi, struct timeval cur_time,
				unsigned long int time_stamp)
{
	dt->one_is_died = 1;
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / ONE_MLSEC), phi->name, " died\n",
		dt);
	//sem_wait(dt->log_lock);
	dt->is_finish = 1;
	sem_post(dt->end_lock);
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
		sem_wait(data->finish_eaten);
		++i;
		if (i == data->n_philo && !data->one_is_died)
		{
			ft_get_time(&cur_time);
			time_stamp = ft_get_time_diff(&cur_time, data->time_start);
			ft_display_log((time_stamp / ONE_MLSEC), "all philos",
				" have eaten\n", data);
			data->is_finish = 1;
			sem_post(data->end_lock);
		}
	}
	return (NULL);
}

void		*death_checker(void *data)
{
	unsigned long int	time_stamp;
	struct timeval		cur_time;
	t_prog_dt			*dt;
	t_philo_dt			*phi;
	int					i;
	
	dt = (t_prog_dt *)data;

	phi = dt->philo;
	i= -1;		
	while (!dt->is_finish && (++i < dt->n_philo))
	{
	//	printf("in monitor phi %s i = %d\n", dt->philo[i], i);
		while(!phi[i].time_last_meal)
			i++;
		// sem_wait(phi[i].meal_time);
		// ft_get_time(&cur_time);
		sem_wait(phi[i].meal_time);
		ft_get_time(&cur_time);
	//	time_stamp = ft_get_time_diff(&cur_time, phi[i].time_last_meal);
		if ((time_stamp = ft_get_time_diff(&cur_time, phi[i].time_last_meal)) > dt->time_to_die)
		{
			ft_death(dt, &phi[i], cur_time, time_stamp);
			break ;
		}
		sem_post(phi[i].meal_time);
		usleep(1);
		if (i == (dt->n_philo - 1))
			i = -1;
	}
	return (NULL);
}