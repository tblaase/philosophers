/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:21:26 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/14 13:39:22 by tblaase          ###   ########.fr       */
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
	int	check;

	i = 0;
	check = 0;
	input->wait = true;
	while (i < input->n_philos && check == 0)
	{
		pthread_mutex_lock(input->i_p_lock);
		input->i_p = i;
		pthread_mutex_unlock(input->i_p_lock);
		check = pthread_create(&philos[i]->thread_id, NULL, &routine, NULL);
		usleep(100);
		i++;
	}
	if (check != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
