NAME = maps
SRC = mini_map.c utils.c mov_player.c intersections1.c raycasting_wall_rendering.c utils2.c \
		parser_texture.c side_functions.c side_funct_2.c get_next_line.c get_next_line_utils.c \
		get_the_map.c errors.c verify_map.c texture_color_element.c \
		first_fill.c node.c parse_rest.c parse_text_colors.c load_textures.c  pixels.c mov_p.c \
		utils11.c utils12.c
CC = cc 
LIBFLGS = -lmlx -framework Appkit -framework OpenGL
OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LIBFLGS) $(OBJ) -o $(NAME)  -g

%.o: %.c cub3d.h
	$(CC)  -g $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) 
re: fclean all