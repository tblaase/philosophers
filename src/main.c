/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:10:08 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/21 15:07:20 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	main(int argc, char **argv)
{
	t_input	*input;

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
	return (EXIT_SUCCESS);
}
