/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/01 16:58:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdio.h>//A ENLEVER
int	main(void)
{
	int		pid;
	int		i;

	i = 1;
	pid = fork();
	if (pid == 0)
	{
		printf("je susi le fils pid = %d\n", getpid());//philo
		sleep(2);
		printf("fin du fils, i = %d\n", i);
		exit (0);
	}
	else if (pid > 0)
	{
		printf("je suis le père pid = %d\n", getpid());//philo
		sleep(1);
		i = 2;
		printf("le père  modifie la variable i %d\n", i);
		sleep(3);
		printf("fin du père i = %d\n", i);
		exit (0);
	}
	else
	{
		perror("fork");
		exit (1);
	}

//	return (0);
}
