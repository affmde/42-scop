.SILENT=

CXX = g++

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

NAME	:= scope
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
GLFW	:= libraries/glfw
GLAD	:= libraries/glad

HEADERS	:= -I includes -I $(GLEW)/build/files/include -I $(GLAD)/include
LIBS	:= $(GLFW)/files/lib/libglfw3.a -lGL -lX11 -lpthread -lXrandr -lXi -ldl
CSRCS	:= libraries/glad/src/glad.c

OBJS_DIR = obj/
CORE_DIR = srcs/
GEOMETRY_DIR = srcs/geometry/
DISPLAY_DIR = srcs/display/
GLAD_DIR = libraries/glad/src/

CORE = main.cpp Parser.cpp Checker.cpp Utils.cpp
GEOMETRY = Vector3f.cpp Vector2f.cpp Vertex.cpp
DISPLAY = Display.cpp
GLAD = glad.c

ALL_SOURCES = $(CORE) $(GEOMETRY) $(DISPLAY)
ALL_OBJS = $(ALL_SOURCES:.cpp=.o) $(GLAD:.c=.o)

OBJS = $(patsubst %, $(OBJS_DIR)%, $(ALL_OBJS))

all: downloadGLFW glfw $(NAME)

glfw:
	@if [ ! -d "$(GLFW)/files" ]; then \
		echo "$(COLOUR_BLUE)Checking GLFW build" && \
		cmake $(GLFW) -B $(GLFW)/build -DCMAKE_INSTALL_PREFIX=$(GLFW)/files \
		-DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF && \
		make -C $(GLFW)/build && make install -C $(GLFW)/build && \
		echo "$(COLOUR_END)"; \
	else \
		echo "$(COLOUR_GREEN)GLFW already built$(COLOUR_END)"; \
	fi

%.o: %.cpp
	@gcc $(CFLAGS) -o $@ -c $< $(HEADERS)


downloadGLFW:
	@if [ ! -d "libraries" ]; then \
		echo "$(COLOUR_GREEN)Creating libraries$(COLOUR_END)"; \
		mkdir libraries; \
		echo "Downloading GLFW repository"; \
		cd libraries && git clone https://github.com/glfw/glfw.git; \
	else \
		echo "$(COLOUR_GREEN)GLFW already present in libraries folder$(COLOUR_END)"; \
	fi

$(NAME): $(OBJS_DIR) $(OBJS)
	@g++ $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(COLOUR_GREEN)Completed$(COLOUR_END)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(COLOUR_RED)Removed objs folder$(COLOUR_END)"

fclean: clean
	@rm -rf $(GLFW)
	@echo "$(COLOUR_RED)Removed GLFW folder$(COLOUR_END)"
	@rm -rf $(NAME)
	@echo "$(COLOUR_RED)Removed executable$(COLOUR_END)"

re: fclean all

.PHONY: all, clean, fclean, re, libmlx

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(COLOUR_BLUE)Object directory created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(GLAD_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(CORE_DIR)%.cpp
	@g++ $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(GEOMETRY_DIR)%.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(DISPLAY_DIR)%.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"
