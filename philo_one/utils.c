/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:01:20 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/23 17:54:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_strlen(const char *str)
{
	int i;

	if(str == NULL)
		return(-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

// char	*ft_strdup(const char *s1)
// {
// 	int		i;
// 	char	*str;

// 	if (!(str = (char *)malloc(sizeof(*str) * ft_strlen(s1) + 1)))
// 		return (NULL);
// 	i = 0;
// 	while (*(s1 + i))
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }


char	*ft_strjoinfree(char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*str) * (ft_strlen(s1) +
						ft_strlen(s2)) + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

int		ft_atoui(char *str, unsigned int *nb)// dans init
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

int		ft_atoi(char *str, int *nb) // dans init
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

int	ft_write_msg(char *msg, int ret)
{
	write(1, msg, ft_strlen(msg));
	return (ret);
}

void			fill_lunbr(long unsigned nbr, char *ptr)
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
	*ptr='\0';
}

void			fill_nbr(int nbr, char *ptr)
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
	*ptr='\0';
}
