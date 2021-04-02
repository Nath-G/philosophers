/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:18:40 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/02 19:38:26 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	ft_death(t_prog_dt *dt, char *phi_name, struct timeval cur_time,
				unsigned long int time_stamp)
{
	dt->is_finish = 1;
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / 1000), phi_name, " died\n");
	if (sem_post(dt->death))
		return ;
}

static void		*death_monitor(void *data)
{
	t_prog_dt	*dt;

	dt = (t_prog_dt *)data;
	while (!dt->is_finish && !dt->one_is_died)//laisser &&
	{
		sem_wait(dt->death);
		dt->one_is_died = 1;
	}
	if (dt->one_is_died)
		ft_kill_process(dt);
	return (NULL);
}
void		*eats_checker(void *data_philo)//changer data_philo en dt
{
	int					i;
	t_prog_dt			*data;
	struct timeval		cur_time;
	unsigned long int	time_stamp;

	data = (t_prog_dt *)data_philo;//changer data_philo en dt
	if (pthread_create(&(data->deaths_thread), NULL, death_monitor, data) < 0)
		return (NULL);
	i = 0;
	while (i < data->n_philo && !data->one_is_died)
	{
		if (sem_wait(data->finish_eaten))
			return (NULL);
		++i;
	}
	data->is_finish = 1;
	if (!data->one_is_died)
	{
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, data->time_start) / ONE_MLSEC;
		printf("%lu All philosophers almost ate %d times!\n", time_stamp,
			data->n_meals);
		ft_kill_process(data);
	}
	return (NULL);
}

void		*death_checker(void *param)
{
	int					i;
	t_philo_dt			*phi;
	unsigned long int	time_stamp;
	struct timeval		cur_time;
	t_prog_dt			*dt;

	i = 0;
	phi = ((t_param *)param)->philo_dt;
	dt = ((t_param *)param)->data;
	while (!dt->is_finish)
	{
		usleep(ONE_MLSEC);
		if (sem_wait(dt->meal_time))
			return (NULL);
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, phi->time_last_meal);
		if ((time_stamp) > dt->time_to_die)
			ft_death(dt, phi->name, cur_time, time_stamp);
		if (sem_post(dt->meal_time))
			return (NULL);
	}
	return (NULL);
}

int	monitor(t_prog_dt *data)
{
	if (data->n_meals != -1 && !data->is_finish)
	{
		if (pthread_create(&(data->eats_thread), NULL, eats_checker, data) < 0)
			return (ft_display_msg(PTHREAD_ERROR));
	}
	else if (pthread_create(&(data->deaths_thread), NULL, death_monitor, data) < 0)
		return (ft_display_msg(PTHREAD_ERROR));
	return (0);
}
