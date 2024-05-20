CC = emcc
CFLAGS = -O3
SRC = ./srcs
HPATH = includes
LIBFT = ./libft/libft.a
MLX_PATH = MLX42/build/
MLX_NAME = libmlx42.a
MLX = $(MLX_PATH)$(MLX_NAME)
LINUXFLAGS = -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' --preload-file images --preload-file test.cub --experimental-wasm-threads --experimental-wasm-bulk-memory -sALLOW_MEMORY_GROWTH 
MLXFLAGS = -I ./includes/ -I ./mlx -I./libft -pthread
CFILES = $(SRC)/main.c \
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
OFILES = $(CFILES:.c=.o)
NAME = cub3d.js

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME) $(LIBFT) $(MLX) $(MLXFLAGS) $(LINUXFLAGS)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -I$(HPATH) -c $< -o $@

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
