#include "libft/internal/vector_int.h"

void	*ft_vector_last(t_vector_int *vec)
{
	if (vec->length == 0)
		return (NULL);
	return (vec->vector[vec->length - 1]);
}
