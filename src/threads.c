/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:21:26 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/03 21:00:26 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	thread_join(void)
{
	int		i;
	int		check;
	t_philo	**philos;

	i = 0;
	check = 0;
	philos = get_philos();
	while (philos[i] != NULL && check == 0)
		check = pthread_join(philos[i++]->thread_id, NULL);
	return (EXIT_SUCCESS);
}

int	thread_creation(t_input *input, t_philo **philos)
{
	int	i;

	i = 0;
	input->wait = true;
	printf("waiting for thread creation of %lld philos\n", input->n_philos);
	while (i + 1 < input->n_philos)
	{
		if (i % 2 == 0)
		{
			input->i_p = i;
			printf("creating philo %d now...\n", i + 1);
			pthread_create(&philos[i]->thread_id, NULL, &routine, NULL); //threads need to wait for each other
			usleep(1000000);
			printf("Finished %d.\n", i + 1);
		}
		i++;
	}
	i = 0;
	while (i < input->n_philos)
	{
		if (i % 2 != 0)
		{
			input->i_p = i;
			printf("creating philo %d now...\n", i + 1);
			pthread_create(&philos[i]->thread_id, NULL, &routine, NULL);
			usleep(1000000);
			printf("Finished %d.\n", i + 1);
		}
		i++;
	}
	input->wait = false;
	input->start_time = get_time();
	printf("waiting for threads to fisnish\n");
	// wait for thread finish
	i = 0;
	while (true)
	{
		while (philos[i]->running == true)
		{
			usleep(10);
		}
		i++;
		if (philos[i] == NULL)
			break ;
	}
	return (EXIT_SUCCESS);
}
