#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "libft/vector.h"
#include "libft/cstring.h"

#include "minishell/parser.h"
#include "minishell/minishell.h"
#include "minishell/lexer.h"
#include "minishell/stat.h"
#include "minishell/error.h"

/*
   static void	token_destroy(t_token *tok)
   {
   free(tok->value);
   free(tok);
   }

   static void	tokenv_destroy(t_vector *tokenv)
   {
   ft_vector_destroy(tokenv, (void *)(void *) &token_destroy);
   }

   static int	print_token(t_token *tok)
   {
   puts(tok->value);
   return (0);
   }
   */

/*
 ** Parse the tokens obtained by the get_token function.
 **
 ** @return	a vector of t_pipelines.
 */

/*
   t_vector	parser_invoke(char *input)
   {
   t_vector			tokv;
   t_token				*tok;
   size_t				i;

   tokv = ft_gc_add(getstat()->tmp_gc, ft_vector_new(20), &tokenv_destroy);
   while (1)
   {
   tok = get_token(&input);
   if (tok == NULL)
   break ;
   ft_vector_append(tokv, tok);
   }

   return (NULL);
   }
   */

static t_simple_command	*simple_command_new(char **input, t_token **tok)
{
	t_simple_command	*sc;

	sc = malloc(sizeof (*sc));
	sc->argv = ft_vector_new(5);
	sc->id = (*tok)->value;
	*tok = get_token(input);
	while (*tok != NULL && *(*tok)->value != '|' && *(*tok)->value != ';')
	{
		ft_vector_append(sc->argv, (*tok)->value);
		*tok = get_token(input);
	}
	return (sc);
}

int		print_commands(t_simple_command *command)
{
	size_t	i;

	i = 0;
	printf("id: %s\n", command->id);
	printf("args: [");
	while (i < ft_vector_length(command->argv))
		printf(" %s,", ft_vector_get(command->argv, i++));
	printf(" ]\n");
	
	return (0);
}

int			print_pipeline(t_vector pipeline)
{
	printf("Printing pipeline:\n");
	ft_vector_foreach(pipeline, &print_commands, NULL);
	return (0);
}

t_vector	pipeline_new(char **input, t_token **tok)
{
	t_vector	pipeline;

	pipeline = ft_vector_new(10);
	while (*tok != NULL)
	{
		ft_vector_append(pipeline, simple_command_new(input, tok));
		if (*tok == NULL || *(*tok)->value != '|')
			return (pipeline);
		*tok = get_token(input);
	}
	error_print(ERROR_TRAILING_PIPE);
	return (pipeline);
}

t_vector	parser_invoke(char *input)
{
	t_token				*tok;
	t_vector			set;

	set = ft_vector_new(5);
	while (1)
	{
		tok = get_token(&input);
		if (tok == NULL)
			break ;
		if (tok->type == TOKEN_WORD)
			ft_vector_append(set, pipeline_new(&input, &tok));
	}
	ft_vector_foreach(set, &print_pipeline, NULL);
	return (set);
}
