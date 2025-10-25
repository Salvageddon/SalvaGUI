Welcome to the SalvaGUI GUI library.

How to use it:

1. Make sure you have SDL3 installed.
2. Create a program in C. Having a main() function is probably recommended but I'm not entirely sure...
3. Call GUI_initSDL() to initialize SDL library.
4. Call GUI_createWindow() to create windows.
5. Call GUI_createGUI() to create GUI base.
6. Call GUI_create...() to create many control types. For example GUI_createLinearView() creates LinearView control.
7. Call GUI_bakeGUI() to bake GUI. Mandatory if you want to render it :)
8. Create a update loop. The same as if you were using only SDL.
9. Call GUI_refreshScreen() to return your screen to refresh your screen every frame.
10. Call GUI_renderGUI() to render your beautiful Graphical User Interface. Make sure you did step 6. or you'll probably get segfault-ed. Idk, I didn't test what would happen...
11. Call GUI_updatePixels to see changes on your window.
12. After you recover from the stroke and severe depression after seeing the GUI and decided to shut down the program, remember to call GUI_destroyWindow() or your computer will start leaking hydrogen that will ignit... uhh I mean memory leaks :)
13. You don't have to call GUI_destroyGUI() as GUI_destroyWindow() already does it. Really. It won't mem-leak. Stop looking at me...
14. Wait, there is no function called GUI_quitSDL()??? Then why the fuck is there GUI_initSDL()???
15. Well, I think you still probably should call SDL_Quit(), idk...
16. return 0;
17. }

Or you can learn how to use it from the main.c file we have included in this repository.

There are also many other functions we didn't mention both in the SalvaGUI Official Usage Manual above or main.c file. Well, good luck with them :)
