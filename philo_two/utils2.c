/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:01:20 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/16 12:37:31 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

char	*ft_sem_name(char *sem_name, char *phi_name)
{
	static char	name[13];
	int			len;
	int			i;
	int			j;

	len = ft_strlen(phi_name);
	i = 0;
	while (sem_name[i] || i < 8)
	{
		name[i] = sem_name[i];
		i++;
	}
	j = 0;
	while (phi_name[j] && name[i + j] && (i + j) < 12)
	{
		name[i + j] = phi_name[j];
		j++;
	}
	name[i + j] = '\0';
	return (name);
}
