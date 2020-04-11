// void set_link_price(int i, int j, int price)
// {
// 	t_links.room_links[i][j] = price;
// 	t_links.room_links[j][i] = price;
// }
//переработать для зануления в случае отсуствия конца и более дешёвых линков
// int map_mark(int i, int price)
// {
// 	int j;
// 	int flag;
// 	int swap;

// 	price++;
// 	j = 0;
// 	flag = -1;
// 	while(j < t_links.max_size)
// 	{
// 		if (t_links.room_links[i][j] != 0)
// 		{
// 			if (t_links.room_links[i][j] > price)
// 			{
				
// 				if (i != t_rooms.end_room_nbr
// 				&& j != t_rooms.end_room_nbr)
// 				{
// 					set_link_price(i, j, -1);// useless
// 					if ((swap = map_mark(j, price)) > flag)
// 						flag = swap;
// 					if (swap >= 0)
// 						set_link_price(i, j, price);
// 				}
// 				else
// 					flag = 1;
// 			}
// 			else
// 				flag = (flag >= 0) ? flag : 0;
// 		}
// 		j++;
// 	}
// 	// if (flag < 0)
// 	// 	remove_link(i);
// 	return (flag);
// }
// 			else
// 				flag = (flag >= 0) ? flag : 0;
// 		}
// 		j++;
// 	}
// 	// if (flag < 0)

// int deixtra_proto2(int i, int price)
// {
// 	int j;
// 	int flag;

// 	price++;
// 			else
// 				flag = (flag >= 0) ? flag : 0;
// 		}
// 		j++;
// 	}
// 	// if (flag < 0)
// 		{
// 			t_links.room_links[i][j] = price;
// 			t_links.room_links[j][i] = price;
// 			if (i != t_rooms.end_room_nbr
// 			&& j != t_rooms.end_room_nbr)
// 			{
// 				if ((deixtra_proto2(j, price)) > 0)
// 					flag++;
// 				else
// 				{
// 					t_links.room_links[i][j] = -1;
// 					t_links.room_links[j][i] = -1;
// 				}
// 			}
// 			else
// 				flag++;
			
// 		}
// 		else if (t_links.room_links[i][j] > 0 && t_links.room_links[i][j] < price)
// 			flag++;
// 		j++;
// 	}
// 	return (flag);
// }
// void error_func(char *str)
// {
// 	printf("%s\n", str);
// 	exit(0);
// }

// int link_search(char *line)
// {
// 	int i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '-')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int rooms_counter(char **lines)
// {
// 	int rooms;
// 	int i;

// 	i = 0;
// 	rooms = 0;
// 	while(lines[i] != '\0')
// 	{
// 		if (lines[i][0] != '#')
// 		{
// 			//check for room overfillment
// 			if (!(link_search(lines[i])))
// 				rooms++;
// 			else
// 				return (rooms);            
// 		}
// 		i++;
// 	}
// 	return (rooms);
// }

// void line_check(char *line)
// {
//     if (line[0] == '#')
//     {
//         if (line[1] == '#')
//         {
//             if (strcmp(line, "##start"))
//             {
//                 t_valid.start++;
//                 //get next line as start 
//             }
//         }
//     }
// }

// int main(int argc, char **argv)
// {    
// 	int fd;
// 	char *pnt;

// 	if (argc < 2)
// 		printf("NO ARG\n");
// 	else if (argc == 2)
// 	{
// 		if (((fd = open(argv[1], O_RDONLY)) > 0) && ((read(fd, pnt,0) == 0)))
// 		{
// 			parser(fd);
// 			close(fd);
// 		}
// 		else
// 			error_fucn("Incorrect format or unreadable file!");
// 	}
// 	else
// 		printf("TO MANY ARGS\n");
// 	return (0);
// }test_links_matrix();

// if (i == 0)
				// 	ft_printf("L%d-%s", room->ant_nbr, t_rooms.room_list[room->room_nbr]);
				// else
				// 	ft_printf(" L%d-%s", room->ant_nbr, t_rooms.room_list[room->room_nbr]);


//версия с рекурсией
// t_room *make_way(int room_nbr, t_room *prev)
// {
//     t_room *curr;
//     int min_nbr;

//     // if (!(curr = (t_room*)malloc(sizeof(t_room))))
// 	// 	error_func("Malloc Error!");
//     curr->room_nbr = room_nbr;
//     curr->ant_nbr = 0;
//     min_nbr = min_price_next_room(room_nbr);
//     if (min_nbr == t_rooms.start_room_nbr)
//         curr->next_room = NULL;
//     else
//         curr->next_room = make_way(min_nbr, &curr);
//     if (room_nbr != t_rooms.end_room_nbr)
//         remove_link(room_nbr);
//     return (&curr);
// }