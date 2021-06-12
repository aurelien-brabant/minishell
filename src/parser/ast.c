#include <stdlib.h>
#include <stdio.h>

#include "minishell/parser.h"

t_ast_node	*ast_node_new(t_token_type type, void *info)
{
	t_ast_node	*node;

	node = malloc(sizeof (*node));
	if (node == NULL)
		return (NULL);
	node->info = info;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

void		ast_node_insert(t_ast_node **root, t_ast_node *node)
{
	t_ast_node	*tmp;

	if (*root != NULL)
		node->parent = *root;
	if (*root == NULL)
		*root = node;
	else
	{
		if (node->type == TOKEN_WORD)
		{
			if ((*root)->type == TOKEN_OR)
				ast_node_insert(&(*root)->right, node);
			else
				ast_node_insert(&(*root)->left, node);
		}
		else if (node->type == TOKEN_OR)
		{
			tmp = *root;
			*root = node;
			(*root)->left = tmp;
			tmp->parent = *root;
			(*root)->parent = NULL;
		}
	}
}

void	ast_make_parents(t_ast_node *root)
{
	if (root->left != NULL)
		ast_print(root->left);

	if (root->right != NULL)
		ast_print(root->right);
}

static void	print(t_ast_node *node)
{
	printf("-------------------------------------\n");
	
	if (node->parent != NULL)
	{
		printf("PARENT INFO\n");

		if (node->parent->type == TOKEN_OR)
			printf("PIPE\n");
		if (node->parent->type == TOKEN_WORD)
			printf("WORD: %s\n", (char *)node->parent->info);
		printf("\n");
	}
	else
		printf("NO PARENT\n");

	if (node->type == TOKEN_OR)
		printf("PIPE\n");
	if (node->type == TOKEN_WORD)
		printf("WORD: %s\n", (char *)node->info);

	printf("-------------------------------------\n");
}

void		ast_print(t_ast_node *root)
{
	if (root->left != NULL)
		ast_print(root->left);
	print(root);
	if (root->right != NULL)
		ast_print(root->right);
}
