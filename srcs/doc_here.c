/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_here.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:30:08 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 16:31:03 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_delimiter(char *delimiter, t_args *args)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_sigaction = heredoc_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	delimiter = args->next->parsed_arg;
	return (delimiter);
}
