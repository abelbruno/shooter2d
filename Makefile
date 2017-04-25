# General Makefile

CC=g++

CFLAGS= -std=gnu++11 -c -Wall

LDFLAGS=

INC= -I/usr/local/include/freetype2

SOURCES= util/shaders_util.cpp util/lodepng.cpp util/oggstream.cpp util/sound.cpp util/soundfx.cpp util/spritefont.cpp util/spritebatch.cpp util/texture2d.cpp util/animation.cpp \
	     StateManagement/Screens/screen.cpp StateManagement/Screens/menuentry.cpp StateManagement/Screens/mainmenuscreen.cpp StateManagement/Screens/gameoverscreen.cpp \
	     StateManagement/Screens/loadingscreen.cpp StateManagement/Screens/gamescreen.cpp StateManagement/Screens/pausescreen.cpp StateManagement/screenmanager.cpp \
		 parallaxingbackground.cpp projectile.cpp enemy.cpp player.cpp game.cpp main.cpp

OBJECTS=$(SOURCES:.cpp=.o)

LIBS     = -lGL -lGLEW -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lopenal -lalut -logg -lvorbis -lvorbisenc -lvorbisfile -lfreetype
#LIBS     = -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lopenal32 -lalut -logg -lvorbis -lvorbisenc -lvorbisfile -lfreetype -lpthread

EXECUTABLE= shooter

.PHONY: all
all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) $(INC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf util/*.o
	rm -rf StateManagement/*.o
	rm -rf StateManagement/Screens/*.o

