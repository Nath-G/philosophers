/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:24:19 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/31 17:27:12 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int					ft_time_initialisation(t_prog_dt *data)
{
	int	i;

	if (gettimeofday(data->time_start, NULL))
		return (ft_display_msg(TIME_ERROR));
	i = -1;
	while (++i < data->n_philo)
		ft_get_time(data->philo[i].time_last_meal);
	return (0);
}

int					ft_get_time(struct timeval *time)
{
	if (gettimeofday(time, NULL))
	{
		ft_display_msg(TIME_ERROR);
		return (1);
	}
	return (0);
}

unsigned long int	ft_get_time_diff(struct timeval *tm1, struct timeval *tm2)
{
	return ((tm1->tv_sec - tm2->tv_sec) * ONE_MICROSEC
					+ (tm1->tv_usec - tm2->tv_usec));
}
