/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:01:20 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/01 16:32:05 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_write_msg(char *msg, int ret)
{
	write(1, msg, ft_strlen(msg));
	return (ret);
}

void	fill_lunbr(long unsigned nbr, char *ptr)
{
	char			c;
	long unsigned	nnbr;
	long long int	pow;

	pow = 10;
	nnbr = nbr;
	while (nnbr /= 10)
		pow *= 10;
	while ((pow /= 10))
	{
		c = (nbr / pow) % 10 + '0';
		*ptr = c;
		ptr++;
	}
	*ptr = '\0';
}

void	fill_nbr(int nbr, char *ptr)
{
	char			c;
	int				nnbr;
	long long int	pow;

	pow = 10;
	nnbr = nbr;
	while (nnbr /= 10)
		pow *= 10;
	while ((pow /= 10))
	{
		c = (nbr / pow) % 10 + '0';
		*ptr = c;
		ptr++;
	}
	*ptr = '\0';
}
