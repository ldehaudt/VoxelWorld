NAME = Vox
SRC = src/Camera.cpp src/Chunk.cpp src/ChunkManager.cpp src/face.cpp\
src/Input.cpp src/Noise.cpp src/RenderObject.cpp src/Shader.cpp \
src/Skybox.cpp src/Tree.cpp src/Water.cpp src/Window.cpp src/main.cpp
OBJ = Camera.o Chunk.o ChunkManager.o face.o Input.o Noise.o RenderObject.o \
Shader.o Skybox.o Tree.o Water.o Window.o main.o
FRAMEWORKS = -framework OpenGl -w
BREW_INC = -I ~/.brew/include
EIGEN_INC = -I ~/.brew/Cellar/eigen/3.3.5/include/eigen3/
STB_INC = -I ./stb
GLFW_LINK = -L ~/.brew/lib -lglfw

RED = "\033[1;38;2;225;20;20m"
ORANGE = "\033[1;38;2;255;120;10m"
YELLO = "\033[1;38;2;255;200;0m"
GREEN = "\033[1;38;2;0;170;101m"
LG = "\033[1;38;2;167;244;66m"
BLUE = "\033[1;38;2;50;150;250m"
PURPLE = "\033[1;38;2;150;75;255m"
WHITE = "\033[1;38;2;255;250;232m"

$(NAME): install obj compile done

clean:
	@echo $(RED)Cleaning o files
	@rm -f $(OBJ)

fclean: clean
	@echo $(RED)Removing excutable
	@rm -f $(NAME)

re:	fclean $(NAME)

install:
ifneq ("$(shell test -e $(HOME)/.brew && echo ex)" , "ex")
	@echo "BREW INSTALLING ..."
	@curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	@echo $(YELLO)INSTALLING glfw: please be patient
endif
	@echo $(WHITE)Checking for graphics library ...
ifneq ("$(wildcard ~/.brew/include/GLFW/glfw3.h)","")
	@echo $(GREEN)"Already installed!"
else
	@brew install glfw
endif
	@echo $(WHITE)Checking for matrix library ...
ifneq ("$(wildcard ~/.brew/Cellar/eigen/3.3.5/include/eigen3)","")
	@echo $(GREEN)"Already installed!"
else
	@brew install eigen
endif
	@echo $(WHITE)Checking for stb_image ...
ifneq ("$(wildcard ./stb/stb_image.h)","")
	@echo $(GREEN)"Already installed!"
else
	@echo $(YELLO)Downloading stb_image ...
	git clone https://github.com/nothings/stb.git stb
endif

obj: $(SRC) src/*.hpp
	@echo $(WHITE)Creating $@
	@g++ -std=c++11 -c $(SRC) $(EIGEN_INC) $(FRAMEWORKS) $(BREW_INC) $(GLFW_LINK) $(STB_INC)

compile : $(OBJ)
	@echo $(WHITE)Making $(NAME)
	@g++ -std=c++11 $(OBJ) -o $(NAME) $(EIGEN_INC) $(FRAMEWORKS) $(BREW_INC) $(GLFW_LINK) $(STB_INC)

done:
	@echo $(GREEN)"Done! =)"
