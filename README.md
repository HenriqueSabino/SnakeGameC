# SnakeGameC
The classic snake game made with Allegro in C

# Steps to build
To build this project you will need the MinGW compiler and the Allegro 4.4.2 library to your PC. To download the MinGW go to https://sourceforge.net/projects/mingw-w64/ and click the green download button. To download the Allegro library go to https://www.allegro.cc/files/?v=4.4 and choose the version that is compatible with your MinGW

# Building
To make a build of this project open a comand prompt in the project folder and type the following commad:<br>
  gcc -L\<your MinGW installation folder here, if it is set on your path variable you don't need to put this\>/bin/ -g sources/*.c -o build/snake.exe -lallegro-4.4.2-monolith-md-debug<br>Go to the project folder and there should be a build folder created with the executable inside
