#include <stdlib.h>
#include <stdio.h>

#include "minishell/lexer.h"
#include "minishell/parser.h"

t_ast_node	*ast_node_new(t_node_type type, void *info)
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

static void	node_swap(t_ast_node **root, t_ast_node *node)
{
	t_ast_node		*tmp;

	tmp = *root;
	*root = node;
	node->left = tmp;
	node->parent = tmp->parent;
	tmp->parent = *root;
}

static void	insert_output_redirection(t_ast_node **root, t_ast_node *node)
{		
	if ((*root)->type == NODE_PIPE)
			ast_node_insert(&(*root)->right, node);
	if ((*root)->type == NODE_WORD || (*root)->type == NODE_REDIR_OUT)
		node_swap(root, node);
}

static void	insert_input_redirection(t_ast_node **root, t_ast_node *node)
{
	if ((*root)->type == NODE_REDIR_IN)
	{
		node->parent = (*root)->parent;
		*root = node;
	}
	else if ((*root)->type == NODE_PIPE)
		ast_node_insert(&(*root)->right, node);
	else
		ast_node_insert(&(*root)->left, node);
}

static void		insert_pipe(t_ast_node **root, t_ast_node *node)
{
	t_ast_node	*tmp;

	tmp = *root;
	*root = node;
	node->left = tmp;
	node->parent = NULL;
	tmp->parent = *root;
}

static void		insert_word(t_ast_node **root, t_ast_node *node)
{
	if ((*root)->type == NODE_REDIR_OUT)
	{
		if ((*root)->right != NULL)
			ast_node_insert(&(*root)->left, node);
		else
			ast_node_insert(&(*root)->right, node);
	}
	else if ((*root)->type == NODE_REDIR_IN && (*root)->right == NULL)
		ast_node_insert(&(*root)->right, node);
	else if ((*root)->type == NODE_REDIR_IN && (*root)->right != NULL)
		node_swap(root, node);
	else if ((*root)->type == NODE_PIPE)
		ast_node_insert(&(*root)->right, node);
	else
		ast_node_insert(&(*root)->left, node);
}

void		ast_node_insert(t_ast_node **root, t_ast_node *node)
{
	if (*root != NULL)
		node->parent = *root;
	if (*root == NULL)
		*root = node;
	else
	{
		if (node->type == NODE_WORD)
			insert_word(root, node);
		else if (node->type == NODE_PIPE)
			insert_pipe(root, node);
		else if (node->type == NODE_REDIR_OUT)
			insert_output_redirection(root, node);
		else if (node->type == NODE_REDIR_IN)
			insert_input_redirection(root, node);
	}
}

static void	print(t_ast_node *node)
{
	printf("-------------------------------------\n");
	
	if (node->parent != NULL)
	{
		printf("PARENT INFO\n");

		if (node->parent->type == NODE_PIPE)
			printf("PIPE\n");
		if (node->parent->type == NODE_WORD)
			printf("WORD: %s\n", (char *)node->parent->info);
		if (node->parent->type == NODE_REDIR_OUT)
			printf("REDIRECTION OUT\n");
		if (node->parent->type == NODE_REDIR_IN)
			printf("REDIRECTION IN\n");
		printf("\n");
	}
	else
		printf("NO PARENT\n");

	if (node->type == NODE_PIPE)
		printf("PIPE\n");
	if (node->type == NODE_WORD)
		printf("WORD: %s\n", (char *)node->info);
	if (node->type == NODE_REDIR_OUT)
		printf("REDIRECTION OUT\n");
	if (node->type == NODE_REDIR_IN)
		printf("REDIRECTION IN\n");

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
