/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:08:21 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/03 11:43:40 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define ONE_MLSEC 1000
# define ONE_MICROSEC 1000000
# define ARG_NB_ERROR -10
# define ARG_FORMAT_ERROR -20
# define ARG_VALUE_ERROR -30
# define MALLOC_ERROR -40
# define PTHREAD_ERROR -50
# define SEM_ERROR -60
# define TIME_ERROR -70
# define ARG_INIT_ERROR -80
# define DATA_INIT_ERROR -90

typedef struct		s_philo_dt
{
	char			*name;
	int				id;
	pthread_t		thread;
	// pthread_t		death_thread;
	struct timeval	*time_last_meal;
	int				meals_ate;
	sem_t			*meal_time;
	int				is_start_sleeping;
}					t_philo_dt;

typedef struct		s_prog_dt
{
	int				n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				n_meals;
	struct timeval	*time_start;
	t_philo_dt		*philo;
	int				one_is_died;
	int				is_finish;
	pthread_t		eats_thread;
	pthread_t		deaths_thread;
	sem_t			*log_lock;
	sem_t			*end_lock;
	sem_t			*finish_eaten;
	sem_t			*fork;
	sem_t			**queue_forks;
}					t_prog_dt;

typedef struct		s_param
{
	t_prog_dt	*data;
	t_philo_dt	*philo_dt;
}					t_param;

/*
**----clean up----**
*/
int					clean_philo(t_prog_dt *data, t_param *param);
void				ft_clean_sem(t_prog_dt *data);
void				ft_post_sem(t_prog_dt *dt);

/*
**----initialisation----**
*/
int					init_prog(int ac, char **av, t_prog_dt *data);
int					init_philo(t_prog_dt *data);

int					init_ml_time_phi_sem(char *sem_name, int phi,
						t_prog_dt	*data);
int					init_data_sem(t_prog_dt *data);
int					init_queue_fork_sem(t_prog_dt *data);

/*
**----liffe actions----**
*/
int					philo_eats(t_philo_dt *phi, t_prog_dt *data);
int					philo_sleeps(t_philo_dt *phi, t_prog_dt *data);
int					philo_thinks(t_philo_dt *phi, t_prog_dt *data);

/*
**----log----**
*/
int					ft_display_msg(int msg_nb);
void				ft_display_log(long unsigned time_stamp, char *philo_name,
						char *msg, t_prog_dt *data);
/*
**----monitoring----**
*/
void				*death_checker(void *param);
void				*eats_checker(void *data);
void				philo_killer(t_prog_dt *data);

/*
**----time----**
*/
int					ft_get_time(struct timeval *time);
unsigned long int	ft_get_time_diff(struct timeval *cur_time,
						struct timeval *time);

/*
**----utils----**
*/
int					ft_check_argument_format(char **av);
int					ft_strlen(const char *str);
int					ft_write_msg(char *msg, int ret);
int					ft_atoui(char *str, unsigned int *nb);
int					ft_atoi(char *str, int *nb);
void				fill_nbr(int nbr, char *ptr);
void				fill_lunbr(long unsigned nbr, char *ptr);
char				*ft_strjoinfree(char *s1, const char *s2);
char				*ft_sem_name(char *sem_name, char *phi_name);
int					ft_usleep(int *is_finish, unsigned int time);

#endif
