/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:57:48 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/15 16:10:25 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

typedef struct s_mv
{
	int	i;
	int	k;
	int	j;
	int	nb_filled;
}t_mv;

typedef struct s_boucle
{
	int	i;
	int	min_result;
}t_boucle;

typedef struct s_list
{
	int				content;
	struct s_list	*back;
	struct s_list	*next;
}t_list;

typedef struct s_dlist
{
	int				length;
	struct s_list	*begin;
	struct s_list	*end;
}t_dlist;

int		is_only_sign(char *input);
int		is_full_space(char *input);
int		check_input_args(char **user_input, t_dlist **stack_a, t_dlist **sb);
int		check_double(char **user_input);
int		len_dlist(t_dlist *lst);
int		is_empty_dlist(t_dlist *lst);
int		is_sort(t_dlist *stack_a);
int		nb_count(long n);
int		ft_strlen(char *str);
int		is_min_stack(t_dlist *stack_a, int nb);
int		r_v(t_list *stack, int index);
int		return_max_index(t_dlist *tmp);
int		ft_check_overflow(char **av, int input_status);
int		min_move3(int *min_result, t_dlist **move_a, t_dlist **move_b, int *i);
int		min_move4(int *min_result, t_dlist **move_a, t_dlist **move_b, int *i);
int		min_move1(int *min_result, t_dlist **move_a, t_dlist **move_b, int *i);
int		min_move2(int *min_result, t_dlist **move_a, t_dlist **move_b, int *i);
int		check_input_args2(int *i, int *j, char **user_input);
int		five_cases_spec(t_dlist *stack_a);
int		is_min_five(t_dlist *stack, int nb);
int		is_max_five(t_dlist *stack, int nb);
int		five_cases_spec2(t_dlist *stack_a);

void	sort_five_spec2(t_dlist **stack_a, t_dlist **stack_b);
void	sort_five_spec(t_dlist **stack_a, t_dlist **stack_b);
void	ft_main_sort(t_dlist **stack_a, t_dlist **stack_b, int input_status);
void	free_one_arg(int ac, int input_status, char **av);
void	move_ra(t_dlist **stack_a, t_dlist **stack_b);
void	move_ra_tmp(t_dlist **stack_a, t_dlist **stack_b);
void	move_rb(t_dlist **stack_b, t_dlist **stack_a);
void	move_rr(t_dlist **stack_a, t_dlist **stack_b);
void	move_rra(t_dlist **stack_a, t_dlist **stack_b);
void	move_rra_tmp(t_dlist **stack_a, t_dlist **stack_b);
void	move_rrb(t_dlist **stack_b, t_dlist **stack_a);
void	move_rrr(t_dlist **stack_a, t_dlist **stack_b);
void	print_stack_a(t_dlist *stack_a);
void	print_stack_b(t_dlist *stack_b);
void	print_stacks(t_dlist *stack_a, t_dlist *stack_b);
void	ft_sort_above_three(t_dlist **stack_a, t_dlist **stack_b);
void	ft_sort_three(t_dlist **stack_a, t_dlist **stack_b);
void	ft_sort_three2(t_dlist **stack_a, t_dlist **stack_b);
void	move_pa(t_dlist **stack_a, t_dlist **stack_b);
void	move_pb(t_dlist **stack_a, t_dlist **stack_b);
void	swap_nodes(int *a, int *b);
void	move_sa(t_dlist **stack_a);
void	move_sb(t_dlist **stack_b);
void	move_ss(t_dlist **stack_a, t_dlist **stack_b);
void	ft_remove_first_node(t_dlist **lst);
void	ft_remove_last_node(t_dlist **lst);
void	ft_lstclear(t_dlist **lst);
void	ft_lstclear_node(t_list **lst);
void	ft_add_first(t_dlist **head, int val, t_dlist **head2);
void	ft_add_last(t_dlist **head, int val, t_dlist **head2);
void	put_min_above(t_dlist **tmp, t_dlist **stack_a);
void	put_min_above_tmp(t_dlist **tmp, t_dlist **stack_a);
void	ft_sort_above_three(t_dlist **stack_a, t_dlist **stack_b);
void	res_ab32(t_dlist **stack_a, t_dlist **stack_b, int *min_index_move);
void	fill_lis_table(int *lis, t_dlist **stack_a);
void	fill_lis_one_two(int *lis, t_dlist **stack_a);
void	apply_lis(int *lis, t_dlist **stack_a, t_dlist **stack_b, t_dlist *tmp);
void	mv(t_dlist **mv_a, t_dlist **mv_b, t_dlist **s_a, t_dlist **s_b);
void	cal_nb1(int *nb_filled, int *i, t_dlist **stack_b, t_dlist **move_b);
void	if_first(t_dlist **move_a, int *nb_filled, t_dlist **stack_a);
void	mv2(t_dlist **stack_a, t_dlist **stack_b, t_dlist **mv_a, t_mv *mv_id);
void	calcul_nb_move_max(t_dlist **move_a, t_dlist **stack_a, int *nb_filled);
void	c_min(t_dlist **ma, t_dlist **mb, t_dlist **stack_b, int *min_id);
void	c_min2(t_dlist **ma, t_dlist **mb, int *min_id, t_boucle *mv_min);
void	mv_min_id(int *min_id_mv, t_list **tmp_move_a, t_list **tmp_move_b);
void	mv_s1(t_list **ta, t_list **tb, t_dlist **stack_a, t_dlist **stack_b);
void	if_end_half(t_dlist **mv_a, t_dlist **stack_a, int *nb_filled, int *k);
void	if_first_half(t_dlist **move_a, int *nb_filled, int *k, t_dlist **sa);
void	mv_s2(t_list **ta, t_list **tb, t_dlist **stack_a, t_dlist **stack_b);
void	second_check(int *input_status, int *ac, char **av);
void	init_dlist(t_dlist **lst);
void	ft_print_stack(t_dlist *stack);
void	init_dlist_begin(t_dlist **lst1, t_dlist **lst2);
void	malloc_error_lis(int *lis, t_dlist **stack_a, t_dlist **stack_b);
void	malloc_error_tmp(int *lis, t_dlist **s_a, t_dlist **s_b, t_dlist **tmp);
void	free_stacks(t_dlist **stack1, t_dlist **stack2);
void	free_end(t_dlist **stack_a, t_dlist **stack_b);

char	**ft_split(char const *s, char c);

long	ft_atoi(const char *str);

#endif
