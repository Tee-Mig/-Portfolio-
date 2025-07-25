/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:53:13 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/21 11:40:28 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_main_sort(t_dlist **stack_a, t_dlist **stack_b, int input_status)
{
	if (*stack_a != NULL && !is_sort(*stack_a) && input_status == 1)
	{
		if (len_dlist(*stack_a) == 2)
		{
			if ((*stack_a)->begin->content
				> (*stack_a)->begin->next->content)
				move_sa(&*stack_a);
		}
		else if (len_dlist(*stack_a) == 3)
			ft_sort_three(&*stack_a, &*stack_b);
		else if (len_dlist(*stack_a) > 3)
		{
			if (len_dlist(*stack_a) == 5 && five_cases_spec(*stack_a))
				sort_five_spec(&*stack_a, &*stack_b);
			else if (len_dlist(*stack_a) == 5 && five_cases_spec2(*stack_a))
				sort_five_spec2(&*stack_a, &*stack_b);
			else
				ft_sort_above_three(&*stack_a, &*stack_b);
		}
	}
	else if (input_status == 0)
		write(1, "Error\n", 6);
}

void	free_one_arg(int ac, int input_status, char **av)
{
	if (ac == 2)
	{
		input_status = -1;
		while (av[++input_status])
			free(av[input_status]);
		free(av);
	}
}

void	free_end(t_dlist **stack_a, t_dlist **stack_b)
{
	ft_lstclear(&*stack_b);
	ft_lstclear(&*stack_a);
	free(*stack_a);
	free(*stack_b);
}

int	main(int ac, char **av)
{
	int		input_status;
	t_dlist	*stack_a;
	t_dlist	*stack_b;

	stack_a = malloc(sizeof(t_dlist));
	stack_b = malloc(sizeof(t_dlist));
	init_dlist_begin(&stack_a, &stack_b);
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		input_status = check_input_args(av, &stack_a, &stack_b);
	}
	else if (ac > 2)
		input_status = check_input_args(av + 1, &stack_a, &stack_b);
	else if (ac == 1)
		input_status = 1;
	else
		input_status = 0;
	second_check(&input_status, &ac, av);
	ft_main_sort(&stack_a, &stack_b, input_status);
	free_one_arg(ac, input_status, av);
	free_end(&stack_a, &stack_b);
	return (0);
}
