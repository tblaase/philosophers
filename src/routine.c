/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:59:25 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/03 21:06:40 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

void	*routine(void *arg)
{
	t_input	*input;
	t_philo	*philo;
	// long	start_time;
	int		eat;

	(void)arg;
	eat = 0;
	input = get_input();
	philo = get_philos()[input->i_p];
	printf("setting the running bool of philo %d to true\n", philo->philo_n);
	philo->running = true;
	printf("%d waiting for thread creation to finish\n", philo->philo_n);
	while (input->wait == true)
		usleep(1);
	// start_time = get_time();
	while (input->n_must_eat[0] == true && eat < input->n_must_eat[1]
		&& eat < INT_MAX - 1) // runs infinite
	{
		philo->time_philo = get_time();
	while ((input->n_must_eat[0] == true && eat < input->n_must_eat[1]
		&& eat < INT_MAX - 1) || (input->n_must_eat[0] == false && eat < INT_MAX)) //test with MAX_INT
	{
		// printf("start_time of %d is %ld\n", philo->philo_n, philo->time_philo - input->start_time);
		// printf("%d trying to grab fork_r now\n", philo->philo_n);
		pthread_mutex_lock(&input->forks[philo->fork_r]);
		print_state(input, philo, grabbed_fork, get_time());
		// printf("%d trying to grab fork_l now\n", philo->philo_n);
		pthread_mutex_lock(&input->forks[philo->fork_l]); // fork_l is probably not working
		print_state(input, philo, grabbed_fork, get_time());
		// if ((start_time - get_time()) >= input->tt_die)
		// 	death_routine(philo);
		if (input->death == false)
		{
			// eat
			print_state(input, philo, is_eating, get_time());
			ft_sleep(input->tt_eat);
			eat++;
			// unlock
			pthread_mutex_unlock(&input->forks[philo->fork_l]);
			pthread_mutex_unlock(&input->forks[philo->fork_r]);
			// start_time = get_time();
			// sleep
			print_state(input, philo, is_sleeping, get_time());
			ft_sleep(input->tt_sleep);
			print_state(input, philo, is_thinking, get_time());
		}
	}
	philo->running = false;
	return (NULL);
}
