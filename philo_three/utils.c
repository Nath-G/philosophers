/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:01:20 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/01 16:32:03 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_strlen(const char *str)
{
	int i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_check_argument_format(char **av)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

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
