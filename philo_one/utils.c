/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:01:20 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/10 19:01:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_str_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_atoui(char *str, unsigned int *nb)
{
	if (*str == '\0')
		return (1);
	*nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		*nb = 10 * *nb + (*str++ - '0');
	if (*str != '\0')
		return (1);
	return (0);
}

int		ft_atoi(char *str, int *nb)
{
	if (*str == '\0')
		return (1);
	*nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		*nb = 10 * *nb + (*str++ - '0');
	if (*str != '\0')
		return (1);
	return (0);
}

int	ft_write_err_msg(char *err_msg, int ret)
{
	write(1, err_msg, ft_str_len(err_msg));
	return (ret);
}

void			fill_nbr(size_t nbr, char *ptr)
{
	char			c;
	size_t			nnbr;
	long long int	pow;
	printf("ok\n");
	pow = 10;
	nnbr = nbr;
	while (nnbr /= 10)
		pow *= 10;
	printf("ok1\n");
	while ((pow /= 10))
	{
		c = (nbr / pow) % 10 + '0';
//		printf("ptr = %s %c ok2\n", ptr, *ptr);
		*ptr = c;
//		printf("ok3\n");
		ptr++;
	}
	*ptr='\0';
}