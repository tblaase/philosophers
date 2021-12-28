/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:10:08 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/28 16:36:31 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	main(int argc, char **argv)
{
	t_input	*input;
	t_philo	**philos;
	int		check;

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
		philos = init_philos(input);
		if (philos == NULL || philos[0] == NULL)
		{
			printf("Error while creating philosophers\n");
			return (EXIT_FAILURE);
		}
		check = thread_creation(input, philos);
		if (check == 0)
		{
			thread_join(philos);
		}
		else
			return (EXIT_FAILURE); //exit_routine(input, philos,exit_status) for freeing everything and exit_status is needed
	}
	return (EXIT_SUCCESS);
}
