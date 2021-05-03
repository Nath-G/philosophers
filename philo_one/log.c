/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:58:49 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/30 14:24:10 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_display_msg(int msg_nb)
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
	if (msg_nb == ARG_INIT_ERROR)
		return (ft_write_msg("Error : at argument initialisation\n", msg_nb));
	if (msg_nb == DATA_INIT_ERROR)
		return (ft_write_msg("Error : at data initialisation\n", msg_nb));
	if (msg_nb == MUTEX_ERROR)
		return (ft_write_msg("Error : at mutex initialisation\n", msg_nb));
	if (msg_nb == TIME_ERROR)
		return (ft_write_msg("Error : at time initialisation\n", msg_nb));
	return (0);
}

void	ft_display_log(long unsigned time_stamp, char *philo_name, char *msg,
		t_prog_dt *data)
{
	int				i;
	char			*ptr;
	//char			*str;
	long unsigned	nbr;

	nbr = time_stamp;
	i = 0;
	while (nbr /= 10)
		i++;
	if (!(ptr = (char *)malloc(sizeof(char) * i + 2)))
	{
		ft_display_msg(MALLOC_ERROR);
		exit(1);
	}
	*ptr = '\0';
	fill_lunbr(time_stamp, ptr);
	// str = ft_strjoinfree(ptr, " ");
	// str = ft_strjoinfree(str, philo_name);
	// str = ft_strjoinfree(str, msg);
	pthread_mutex_lock(&data->output_protection);
	if (!data->is_finish)
	{
		write(1, ptr, ft_strlen(ptr));
		write(1, " ", 1);
		write(1, philo_name, ft_strlen(philo_name));
		write(1, msg, ft_strlen(msg));

	}
	//	write(1, str, ft_strlen(str));
			free(ptr);
	pthread_mutex_unlock(&data->output_protection);
	// if (// free(ptr);
}
