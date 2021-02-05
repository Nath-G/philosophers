/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/02 15:53:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdio.h>//A ENLEVER
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void	*my_thread_process(void *arg)
{
	int i;

	i = 0;
	while (i < 5)
	{
		printf("philo %s: état %d\n", (char*)arg, i);
		sleep(1);
		i++;
	}
	pthread_exit(0);
}

int	main(void)
{
	pthread_t	th1;
	pthread_t	th2;
	void		*ret;
	
		if (pthread_create(&th1, NULL, my_thread_process, "1") < 0)
		{
			printf("error phtread 1\n");
			exit (1);
		}
		if (pthread_create(&th2, NULL, my_thread_process, "2") < 0)
		{
			printf("error phtread 2\n");
			exit (1);
		}
	(void)pthread_join(th1, &ret);
	(void)pthread_join(th2, &ret);
//	return (0);
}
