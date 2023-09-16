#include "shell.h"

/**
 * _realloc - Reallocates a memory on a block
 * @ptr: Pointer to the memory to be reallocated
 * @old_sz: Size in bytes of the actual allocated memory
 * @new_sz: Size in bytes for the new allocated memory
 *
 * Return:Pointer to the newly allocated memory
 */
void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz)
{
	int limit, i;
	void *pointer;

	if (old_sz == new_sz)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_sz));

	if (new_sz == 0)
	{
		free(ptr);
		return (NULL);
	}

	pointer = malloc(new_sz);

	if (old_sz > new_sz)
		limit = new_sz;
	else
		limit = old_sz;

	for (i = 0; i < limit; i++)
		((char *)pointer)[i] = ((char *)ptr)[i];

	free(ptr);

	return (pointer);
}
