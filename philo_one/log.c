/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:58:49 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/24 15:59:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_display_msg(int msg_nb)
{
	if (msg_nb == ARG_NB_ERROR)
		return (ft_write_msg("Error : wrong argument number!\n", msg_nb));
	if (msg_nb == ARG_FORMAT_ERROR)
		return (ft_write_msg("Error : argument format\n", msg_nb));
	if (msg_nb == ARG_VALUE_ERROR)
		return (ft_write_msg("Error : argument value\n", msg_nb));
	if (msg_nb == MALLOC_ERROR)
		return (ft_write_msg("Error : memory allocation\n", msg_nb));
	if (msg_nb == PTHREAD_ERROR)
		return (ft_write_msg("Error : at pthread creation\n", msg_nb));
	return (0);
}

int		ft_get_time(struct timeval *cur_time)
{
	if (gettimeofday(cur_time, NULL)) //!(i = 0) && ...dans la condition
	{
		//clean nd free
		ft_display_msg(TIME_ERROR);
		exit (1);//il faut faire un return (1) et free dans la fonction précédente.
	}
	return (0);
}	

void	ft_display_log(long unsigned time_stamp, char *philo_name, char *msg)
{
	char	*ptr;
	char	*str;
	int		i;
	long unsigned nbr;

	nbr = time_stamp;
	i = 0;
	while (nbr /= 10)
		i++;
	if (!(ptr = (char *)malloc(sizeof(char) * i + 2)))
	{
		//clean
		ft_display_msg(MALLOC_ERROR);
		exit (1);//il faut faire un return et free la fonction précédente
	}
	*ptr = '\0';
	//pthread_mutex_lock(lock_log_display);
	fill_lunbr(time_stamp, ptr);
	str = ft_strjoinfree(ptr, " ");
	str = ft_strjoinfree(str, philo_name);
	str = ft_strjoinfree(str, msg);
	write(1, str, ft_strlen(str));
	free(str);
}
