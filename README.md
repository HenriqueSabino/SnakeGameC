# SnakeGameC
The classic snake game made with Allegro in C

# to build
To build this project you will need the MinGW compiler and the Allegro 4.4.2 library to your PC. To download the MinGW go to https://sourceforge.net/projects/mingw-w64/ and click the green download button. To download the Allegro library go to https://www.allegro.cc/files/?v=4.4 and choose the version that is compatible with your MinGW

# Building
To make a build of this project open a comand prompt in the source folder and type the following commad:<br>
  gcc -L\<your MinGW installation folder here\>/bin/ -g \<all of the .c files in the folder separated by spaces\> -o snake.exe -lallegro-4.4.2-monolith-md-debug -lallegro-4.4.2-monolith-md
