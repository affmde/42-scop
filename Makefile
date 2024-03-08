.SILENT=

CXX = g++

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

NAME	:= scope
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
GLFW	:= libraries/glfw
GLEW	:= libraries/glew

HEADERS	:= -I includes -I $(GLFW)/files/include -I $(GLEW)/build/files/include
LIBS	:= $(GLEW)/build/build/lib/libGLEW.a $(GLFW)/files/lib/libglfw3.a -lGL -lX11 -lpthread -lXrandr -lXi -ldl
SRCS	:= $(shell find ./srcs -iname "*.c")
OBJS	:= ${SRCS:.cpp=.o}

OBJS_DIR = obj/
CORE_DIR = srcs/
GEOMETRY_DIR = srcs/geometry/
DISPLAY_DIR = srcs/display/

CORE = main.cpp Parser.cpp Checker.cpp Utils.cpp
GEOMETRY = Vector3f.cpp Vector2f.cpp Vertex.cpp
DISPLAY = Display.cpp

ALL_SOURCES = $(CORE) $(GEOMETRY) $(DISPLAY)
ALL_OBJS = $(ALL_SOURCES:.cpp=.o)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(ALL_OBJS))

all: downloadGLFW glfw downloadGLEW glew $(NAME)

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

glew:
	@if [ ! -d "$(GLEW)/build/files" ]; then \
		echo "$(COLOUR_BLUE)Checking GLEW build" && \
		cmake $(GLEW)/build/cmake -B $(GLEW)/build/build -DCMAKE_INSTALL_PREFIX=$(GLEW)/build/files && \
		make -C $(GLEW)/build/build && make glew_s -C $(GLEW)/build/build && \
		echo "$(COLOUR_END)" && \
		mkdir -p $(GLEW)/build/files/lib && \
		cp $(GLEW)/build/build/lib/libGLEW.a $(GLEW)/build/files/lib; \
	else \
		echo "$(COLOUR_GREEN)GLEW already built$(COLOUR_END)"; \
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

downloadGLEW:
	@if [ ! -d "libraries/glew" ]; then \
		echo "$(COLOUR_GREEN)Creating libraries$(COLOUR_END)"; \
		mkdir libraries; \
		echo "Downloading GLEW repository"; \
		cd libraries && git clone https://github.com/Perlmint/glew-cmake.git glew; \
	else \
		echo "$(COLOUR_GREEN)GLEW already present in libraries folder$(COLOUR_END)"; \
	fi

cglue:
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS_DIR) $(OBJS)
	@g++ $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(COLOUR_GREEN)Completed$(COLOUR_END)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(COLOUR_RED)Removed objs folder$(COLOUR_END)"

fclean: clean
	@rm -rf $(GLEW)
	@echo "$(COLOUR_RED)Removed GLEW folder$(COLOUR_END)"
	@rm -rf $(GLFW)
	@echo "$(COLOUR_RED)Removed GLFW folder$(COLOUR_END)"
	@rm -rf libraries
	@echo "$(COLOUR_RED)Removed libraries folder$(COLOUR_END)"
	@rm -rf $(NAME)
	@echo "$(COLOUR_RED)Removed executable$(COLOUR_END)"

re: fclean all

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

$(OBJS_DIR)%.o: $(DISPLAY_DIR)%.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@ $(HEADERS)
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

glu: $(OBJS_DIR)glew.o

$(OBJS_DIR)glew.o: srcs/glew.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)