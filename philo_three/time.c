/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:24:19 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/01 16:32:00 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
