pathToLibraryDiani = /home/diani/Downloads
pathToLibraryValesska = /home/valesska/Desktop/ANPI/Tarea1_Grupo1

main: main.cpp funtras.cpp
	c++ -I ${pathToLibraryDiani}/boost_1_81_0 main.cpp -o main
