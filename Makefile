CFLAGS		= -O3
CFILES		= $(SRC)/main.c \
		  $(SRC)/image.c \
	 	  $(SRC)/doors.c \
		  $(SRC)/sprites.c \
		  $(SRC)/parse_cub_file.c \
		  $(SRC)/parse_map.c \
	 	  $(SRC)/utils_parse_map.c \
	 	  $(SRC)/utils_parse_map_2.c \
	 	  $(SRC)/parse_textures.c \
		  $(SRC)/minimap.c \
		  $(SRC)/cast_rays.c \
		  $(SRC)/draw.c \
		  $(SRC)/key_events.c \
		  $(SRC)/utils_textures.c \
		  $(SRC)/utils_minimap.c \
		  $(SRC)/utils_colors.c \
	 	  $(SRC)/sprites_utils.c \
	 	  $(SRC)/player_move.c \
	 	  $(SRC)/initialize_params.c \
	 	  $(SRC)/draw_doors.c
OFILES		= $(CFILES:.c=.o)
NAME		= cub3d.js
SRC		= ./srcs
LIB		= cub3d.a
HPATH		= includes
MLXFLAGS	= -I ./includes/ -I ./mlx -I./libft -pthread
LINUXFLAGS	= -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1
MACFLAGS	= # Adjust as necessary for MacOS
MLX_PATH	= MLX42/build/
MLX_NAME	= libmlx42.a
MLX		= $(MLX_PATH)$(MLX_NAME)
LIBFT		= ./libft/libft.a
CC			= emcc

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME) $(LIBFT) $(MLX) $(MLXFLAGS) $(LINUXFLAGS)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -I$(HPATH) -c $< -o $@

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -f $(NAME) $(LIB)

re: fclean all

