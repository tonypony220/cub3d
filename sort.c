#include "cub3d.h"

void		swap(int *fst, int *sec)
{
	int		tmp;

	tmp = *fst;
	*fst = *sec;
	*sec = tmp;
}

void		selection_sorting_sprite(double arr_val[], int arr_pos[], int n)
{
	int		i;
	int		j;
	int		min_idx;

	i = -1;
	while (++i < n - 1)
	{
		min_idx = i;
		j = i;
		while (++j < n)
			if (arr_val[j] > arr_val[min_idx])
				min_idx = j;
		swap(&arr_pos[min_idx], &arr_pos[i]);
	}
}
