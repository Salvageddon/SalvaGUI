sdlinc = -Lsrc/lib
sdlarg = -lsdl3 -lmingw32

guiinc = src/include/salvagui
guisrc = src/source

obj = src/obj

all: src/source/main.c
	gcc -c -fPIC ${guisrc}/GUI.c -o ${obj}/GUI.o
	gcc ${sdlinc} -L. -shared ${obj}/GUI.o -o ./SalvaGUI.dll ${sdlarg} -llist
	gcc ${sdlinc} -L. $^ -o ./test ${sdlarg} -llist -lSalvaGUI