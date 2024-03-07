.SILENT=

CXX = g++

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

NAME	:= scope
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= libraries/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include -I includes
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find ./srcs -iname "*.cpp")
OBJS	:= ${SRCS:.cpp=.o}

OBJS_DIR = obj/
CORE_DIR = srcs/
GEOMETRY_DIR = srcs/geometry/

CORE = main.cpp Parser.cpp Checker.cpp Model.cpp Utils.cpp
GEOMETRY = Vertice.cpp VerticeTexture.cpp

ALL_SOURCES = $(CORE) $(GEOMETRY)
ALL_OBJS = $(ALL_SOURCES:.cpp=.o)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(ALL_OBJS))

all: downloadMLX libmlx $(NAME)

libmlx:
	@echo "$(COLOUR_BLUE)Checking MLX build" && \
	cmake $(LIBMLX) -B $(LIBMLX)/build  && make -C $(LIBMLX)/build -j4 >/dev/null && \
	echo "$(COLOUR_END)"

%.o: %.cpp
	@echo "HERE!!!!!!!!!"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

downloadMLX:
	@if [ ! -d "libraries" ]; then \
		echo "$(COLOUR_GREEN)Creating libraries$(COLOUR_END)"; \
		mkdir libraries; \
		echo "Downloading MLX repository"; \
		cd libraries && git clone https://github.com/codam-coding-college/MLX42.git; \
	else \
		echo "$(COLOUR_GREEN)MLX already present in libraries folder$(COLOUR_END)"; \
	fi

$(NAME): $(OBJS_DIR) $(OBJS)
	@g++ $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(COLOUR_GREEN)Completed$(COLOUR_END)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(COLOUR_RED)Removed objs folder$(COLOUR_END)"

fclean: clean
	@rm -rf $(LIBMLX)
	@echo "$(COLOUR_RED)Removed MLX42 folder$(COLOUR_END)"
	@rm -rf libraries
	@echo "$(COLOUR_RED)Removed libraries folder$(COLOUR_END)"
	@rm -rf $(NAME)
	@echo "$(COLOUR_RED)Removed executable$(COLOUR_END)"

re: clean all

.PHONY: all, clean, fclean, re, libmlx

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(COLOUR_BLUE)Object directory created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(CORE_DIR)%.cpp
	@g++ $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(GEOMETRY_DIR)%.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"