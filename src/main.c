/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:10:08 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/05 20:52:18 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	main(int argc, char **argv)
{
	t_input	*input;
	t_philo	**philos;
	// int		check;

	input = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong input!\nplease use like './philo\
		number_of_philosophers time_to_die time_to_eat time_to_sleep\
		[number_of_times_each_philosoppher_must_eat]'\n");
		return (EXIT_FAILURE);
	}
	input = set_input(argv);
	if (input == NULL)
		return (EXIT_FAILURE);
	else
	{
		philos = init_philos(true);
		if (philos == NULL || philos[0] == NULL)
		{
			printf("Error while creating philosophers\n");
			return (EXIT_FAILURE);
		}
		if (thread_creation(input, philos) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		// if (check == 0)
		// 	thread_join();
		// else
		// 	return (EXIT_FAILURE); //exit_routine(input, philos,exit_status) for freeing everything and exit_status is needed
	}
	return (EXIT_SUCCESS);
}
