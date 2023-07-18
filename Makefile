CXX = c++
# CXX = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.36.32532\bin\HostX64\x64\cl.exe"
#CXX = cl
CXXFLAGS = 
NAME = ft_irc_client.exe
RM = del /Q


#LIBS =	/link \
		/LIBPATH:".\lib" \
		glfw386.lib \
		opengl32.lib \
		/LIBPATH:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.36.32532\lib\x64" \
		/LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x64" \
		/LIBPATH:"C:\Program Files (x86)\Windows Kits\10\lib\10.0.22000.0\ucrt\x64" \

LIBS =	-L./lib \
		-lglfw3 -lgdi32

INCLUDES = -I./include -I./include/imgui

SRCPATH = srcs

SRCFILES = main.cpp

IMGUI_SRCPATH = $(SRCPATH)/imgui

IMGUI_SRCFILES = imgui.cpp \
				imgui_draw.cpp \
				imgui_impl_glfw.cpp \
				imgui_impl_opengl3.cpp \
				imGui_stdlib.cpp \
				imgui_tables.cpp \
				imgui_widgets.cpp 

OBJPATH = objs

#OBJFILES = $(SRCFILES:.cpp=.obj) $(IMGUI_SRCFILES:.cpp=.obj)
OBJFILES = $(SRCFILES:.cpp=.o) $(IMGUI_SRCFILES:.cpp=.o)

SRCS = $(addprefix $(SRCPATH)/, $(SRCFILES)) $(addprefix $(IMGUI_SRCPATH)/, $(IMGUI_SRCFILES))

OBJS = $(addprefix $(OBJPATH)/, $(OBJFILES))

.PHONY: all clean fclean re init


all: $(NAME)

#$(OBJPATH)/%.obj: $(SRCPATH)/%.cpp init
#	$(CXX) /c $(CXXFLAGS) $(INCLUDES) /Fo$@ $<

#$(OBJPATH)/%.obj: $(IMGUI_SRCPATH)/%.cpp init
#	$(CXX) /c $(CXXFLAGS) $(INCLUDES) /Fo$@ $<

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp init
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

$(OBJPATH)/%.o: $(IMGUI_SRCPATH)/%.cpp init
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

init:
	-mkdir $(OBJPATH)

#$(CXX) $^ $(LIBS) /Fe$@
$(NAME): $(OBJS)
	$(CXX) $^ $(LIBS) -o $@
	
clean:
	-$(RM) $(OBJPATH)

fclean: clean
	-$(RM) $(NAME)

re: fclean all
