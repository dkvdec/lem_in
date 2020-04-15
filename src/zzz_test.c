#include "../inc/lem_in.h"

///////////////////////////////////////
void	test_room_list()
{
	int i;

	i = 0;
	while (t_rooms.room_list[i])
		ft_printf("%s\n", t_rooms.room_list[i++]);
}
void	test_links_matrix()
{
	int i;
	int j;

	i = 0;
	ft_printf(">>>LINK MATRIX\n");
	while (i < t_links.max_size)
	{
		j = 0;
		while (j < t_links.max_size)
			ft_printf("%-12d", t_links.room_links[i][j++]);
		ft_printf("\n");
		i++;
	}
}
///////////////////////////////////////
void show_ways()
{
	t_way *curr;
	t_room *room;

	curr = t_move.head;
	while (curr != NULL)
	{
		ft_printf("______________________\nway_nbr = %d\nway_length = %d\n", curr->way_nbr, curr->lenght);
		room = curr->start_room;
		ft_printf("|%s|->", t_rooms.room_list[t_rooms.start_room_nbr]);
		while (room != NULL)
		{
			ft_printf("|%s|", t_rooms.room_list[room->room_nbr]);
			if (room->room_nbr != t_rooms.end_room_nbr)
				ft_printf("->");
			room = room->next_room;
		}
		ft_printf("\n");
		curr = curr->next;
	}
}