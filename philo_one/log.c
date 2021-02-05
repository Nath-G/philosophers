/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:58:49 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/04 18:51:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_display_error_msg(int error_nb)
{
	if (error_nb == ARG_NB_ERROR)
		return (ft_write_err_msg("Error : wrong argument number!\n", error_nb));
	if (error_nb == ARG_FORMAT_ERROR)
		return (ft_write_err_msg("Error : argument format\n", error_nb));
	if (error_nb == ARG_VALUE_ERROR)
		return (ft_write_err_msg("Error : argument value\n", error_nb));
	if (error_nb == PTHREAD_ERROR)
		return (ft_write_err_msg("Error : at pthread creation\n", error_nb));
	return (0);
}
