/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 12:30:11 by abrabant          #+#    #+#             */
/*   Updated: 2021/06/27 00:24:54 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ABSTRACT DATA TYPE for vector
*/

#ifndef VECTOR_H
# define VECTOR_H
# include <stdbool.h>
# include "libft/internal/vector_int.h"

typedef void *t_vector; /* abstraction */

t_vector	*ft_vector_new(int capacity);

/*
** Append the element el to the end of the vector arr.
**
** Time complexity: O(1). Will increase if vector resizing is required
** for storing the new element.
*/

void		ft_vector_append(t_vector a, void *el);

/*
** Set the element at index i to el.
** NOTE: No out of bounds check is performed, so make sure the value of is is
** relevant.
**
** Time complexity: O(1) (in all cases).
*/

void		ft_vector_set(t_vector a, void *el, size_t index);

/*
** Get the element at index i of a.
** If index is out of bounds, NULL is returned.
**
** Time complexity: O(1) (in all cases).
*/

void		*ft_vector_get(t_vector a, size_t index);

/*
** Get the last element of a vector
** If there's no element in the vector, NULL is returned.
*/

void		*ft_vector_last(t_vector_int *vec);

size_t		ft_vector_length(t_vector a);

/*
** Set the length of the vector to length. Useful if the size of the vector
** needs to be truncated for some reason, without using successive removes.
*/

void		ft_vector_set_length(t_vector_int *a, size_t length);

size_t		ft_vector_size(t_vector a);

size_t		ft_vector_capacity(t_vector a);

/*
** Duplicates an vector.
**
** Time complexity: O(n) where n is the number of elements in a.
*/

t_vector	ft_vector_dup(t_vector a);

/*
** Concatenate two vectors in as a new one. No destroy operation is done
** on the two vectors passed as arguments.
**
** Time complexity: O(n + m) where n is the number of elements in the first
** vector, and m the number of elements in the second one.
*/

t_vector	ft_vector_concat(t_vector a1, t_vector a2);

/*
** Merge two sorted vectors into a new one.
** The cmp function is used to compare the elements.
*/

t_vector	ft_vector_merge(t_vector a1, t_vector a2,
				int (*cmp)(void *el1, void *el2));

/*
** Perform the union operation on the two vectors passed as arguments, and
** put the result in a new vector. The cmp function is used to know how to
** compare two items between vectors.
**
** Time complexity: O(n^2). The complexity is high because of the many
** searches that need to be performed in order to copy a2. If the two
** vectors are sorted, then it is recommended to use ft_vector_sunion for
** lower time complexity.
*/

t_vector	ft_vector_union(t_vector a1, t_vector a2,
				int (*cmp)(void *, void *));

/*
** Union operation on vectors, like ft_vector_union, but optimized for sorted
** vectors.
** NOTE: due to 42's norm restrictions, an additional overhead related to the 
** way the function has been coded may be expected. This will be fixed when norm
** will no longer be required.
**
** Time complexity: O(n)
*/

t_vector	ft_vector_sunion(t_vector a1, t_vector a2,
				int (*cmp)(void *, void *));

/*
** Perform the inter operation on the two vectors passed as arguments, and put
** the result in a new vector. The cmp function is used to know how to compare
** two items between vectors.
**
** Time complexity: O(n^2). If the vectors are sorted according to cmp,
** ft_vector_sinter is a better choice as it reduces the complexity of the
** operation on sorted vectors.
*/

t_vector	ft_vector_inter(t_vector a1, t_vector a2,
				int (*cmp)(void *, void *));

/*
** Inter operation on vectors, like ft_vector_inter, but optimized for sorted
** vectors.
** NOTE: due to 42's norm restrictions, an additional overhead related to the 
** way the function has been coded may be expected. This will be fixed when norm
** will no longer be required.
**
** Time complexity: O(n)
*/

t_vector	ft_vector_sinter(t_vector a1, t_vector a2,
				int (*cmp)(void *, void *));

/*
** Perform substraction operation on a1 and a2, and put the result in a new
** vector which is returned.
** Substraction operation on vector is a logical operation which excludes
** any element present in the vector 2 from the vector 1.
** Size of the new vector is a1's size.
**
** Time complexity: O(n^2).
** NOTE: If vectors are sorted according to cmp, using ft_vector_ssub is prefered
** as it involves lower time complexity.
*/

t_vector	ft_vector_sub(t_vector a1, t_vector a2,
				int (*cmp)(void *, void *));

/*
** Sub operation on vectors, like ft_vector_sub, but optimized for sorted
** vectors.
** NOTE: due to 42's norm restrictions, an additional overhead related to the
** way the function has been coded may be expected. This will be fixed when norm
** will no longer be required.
**
** Time complexity: O(n)
*/

t_vector	ft_vector_ssub(t_vector a1, t_vector a2,
				int (*cmp)(void *, void *));

/*
** Insert an element at a given index.
**
** Time complexity: worst = O(n) / best = O(1)
** Additional time will be taken if vector needs to be resized in order to
** perform the insert operation, but the time complexity will never exceed O(n).
*/

void		ft_vector_insert(t_vector a, void *el, size_t index);

/*
** Insert an element in a sorted vector. Useful if keeping an vector sorted
** through insertions is wanted. Used as a replacement for the traditional
** append function, but for sorted vectors.
** The cmp function is used to compare two elements: the first is the inserted
** element, the second can be any element already present in the vector.
**
** Time complexity: worst = O(n) / best = O(1)
*/

void		ft_vector_sinsert(t_vector a, void *el,
				int (*cmp)(void *el1, void *el2));

/*
** Sort the vector using a given comparison function and sorting algorithm
*/

void		ft_vector_sort(t_vector_int *a, void (*alg)(void *, size_t, size_t,
					int (*cmp)(void *, void *)), int (*cmp)(void *, void *));

/*
** Determine if vector is sorted or not.
** The cmp function should compare two elements and tell if element 1 is
** indeed less than than el2.
**
** Time complexity: worst = O(n) / best = O(1)
*/

bool		ft_vector_issorted(t_vector a, int (*cmp)(void *el1, void *el2));

/*
** Shift the vector in left or right direction, filling the missing elements
** with zero.
** The direction of the shift is specified using shiftdir. -1 means left shift,
** while 1 means right shift.
** The offset describes how many elements needs to be shifted.
**
** Time complexity: O(n)
*/

void		ft_vector_shift(t_vector a, char shiftdir, size_t offset);

/*
** Rotate the vector in left or right direction.
** The direction of the rotation is specified using rotatedir. -1 means
** rotate to the left while 1 means rotate to the right. The number of elements
** to rotate is passed as the offset parameter.
**
** FIXME: the rotate implementation is currently making use of a pretty naive
** approach. Rotations are done one by one, repeatingly until the expected
** number of rotations has been performed. Therefore the time complexity
** involved by such an approach is O(n * d) where d is the number of rotations
** that are performed. It is possible to reduce the complexity to O(n)
** without making use of a temporary vector, by using a juggling algorithm.
** Ressource: https://www.geeksforgeeks.org/vector-rotation/
**
** Such an algorithm hasn't been implemented because of my low interest
** for the rotate capability in general.
*/

void		ft_vector_rotate(t_vector a, char rotatedir, size_t offset);

/*
** NOTE: this searching method should not be used if you want the order of
** the elements in the vector to stay relevant. If you're using sorted ADT
** vectors, you should absolutely use ft_vector_binsearch instead.
**
** Search for the index of a particular element. The cmp function
** is called on every element to check if it corresponds to the one which
** is searched. Return value of zero means that the element is the searched one.
** The reference element used for the search is passed to ft_vector_search and
** to the cmp function.
**
** This search function uses linear search combined with transposition
** strategy in order to optimize future searches based on search recurrence.
**
** Time complexity: worst = O(n) / best = O(1).
** NOTE: Transposition strategy attempts to decrease complexity when searching
** for often searched values.
*/

int			ft_vector_linsearch(t_vector a, void *ref,
				int cmp(void *ref, void *el));

/*
** NOTE: to get relevant results, the vector NEEDS TO BE SORTED according to
** what the cmp function defines as sorted. If you don't want to deal with
** a sorted vector and need to perform a search operation, use
** ft_vector_linsearch instead.
**
** Use the cmp function to search for an element in the vector. The cmp function
** takes the ref parameter as well as each tested vector element, and compare
** them. If cmp returns zero, then the searched element has been found. The
** search is performed using a binary search algorithm, thus it is way faster
** than ft_vector_linsearch. However, it requires the vector to be sorted.
**
** Time complexity: worst && average = O(log(n)) / best = O(1)
*/

int			ft_vector_binsearch(t_vector a, void *ref,
				int cmp(void *ref, void *el));

/*
** Determines if vector a doesn't have any duplicate. For that, ft_vector_uniq
** returns the index of the first duplicate found (beginning at index 0) or -1
** if no duplicate has been found.
**
** Time complexity: worst = O(n^2) / best = O(1). If vectors are sorted according
** to cmp, use ft_vector_suniq instead for lower time complexity.
*/

int			ft_vector_uniq(t_vector a, int cmp(void *, void *));

/*
** Same than ft_vector_uniq, but optimized for a sorted vector.
*/

int			ft_vector_suniq(t_vector a, int cmp(void *, void *));

/*
** Delete the element at index i in the vector a.
** fn can be provided to do some cleanup related to the element.
** If no such cleanup is needed, NULL can be passed.
**
** Time complexity: worst = O(n) / best = O(1). Smaller index relatively to
** the total size of the vector will lead to higher time complexity.
*/

void		ft_vector_delete(t_vector a, size_t i, void (*fn)(void *el));

/*
** Reverse the order of the elements in the vector
**
** Time complexity: O(n)
*/

void		ft_vector_reverse(t_vector a);

/*
** For each element in the vector, execute the fn function.
**
** The fn function can take up to 3 arguments, in that order:
**   - the actual element (passed as void *)
**   - the index of the element in the vector (passed as int)
**   - any additional data to use inside the function (passed as void *). This
**   data needs to be passed to ft_vector_foreach. If no data is required, NULL
**   can be passed.
**
** The return value of fn is checked after each call: if its return value
** is NOT zero, it means an error occured in fn. If so, the foreach iteration
** will stop and ft_vector_foreach will return this non-zero value.
*/

int			ft_vector_foreach(t_vector a, int (*fn)(), void *data);

/*
** Destroy the vector ADT as well as the content of its members if needed.
**
** The function fn is used to do some cleanup for the members of the vector
** but NULL can be passed if no such cleanup is needed.
*/

void		ft_vector_destroy(t_vector a, void (*fn)(void *el));

/*
** Get the internal representation of the array stored in vec, which is an
** array of pointers. This does	__NOT__ copy it, it only returns its address
** in memory. Any modifications done to it will affect the vector itself.
** It can be especially useful to avoid excessive casting or to pass to
** an array to other functions.
**
** Let's consider, as an example, the following assignment:
** char **strings = ft_vector_get_array(vec);
** That's it, we've got our string array directly using the vector_get_array
** function. Awesome.
**
** NOTE: to make it really handy, this array is always terminated by a NULL
** pointer, to make iterating on it really convenient.
*/

void		**ft_vector_get_array(t_vector_int *vec);

#endif
