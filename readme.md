# Project Title

MazeSolve

## Getting Started

The idea for the project came from a YouTube video on the computerphile channel; the solution is implemented in Python, and not knowing Python I challenged myself to write a Djikstra's algorithm solver in c++. All credit for the mazes goes to Dr. Mike Pound; [find a link to his project here.](https://github.com/mikepound/mazesolving). Credit for the QGraphicsViewZoom implementation goes to Pavel Strakhov on StackOverflow; [link](https://stackoverflow.com/questions/19113532/qgraphicsview-zooming-in-and-out-under-mouse-position-using-mouse-wheel)


### Prerequisites

Using a standard Ubuntu installation, you'll have to obtain the Qt5 and QtCreator packages in order to compile and run this code for your architecture. All you should need to do is run this command
...
sudo apt-get install qtcreator
...
in the terminal emulator, which will install the QtCreator package and all its dependencies. From there you can run the code by opening the .pro file in the maze subdirectory from this readme.

### Installing

No installation process is required for this package. Just QtCreator as above.

## Running the solver

Once you have installed everything and it runs, the code will present a file open dialog. Use this to select a maze in the mazes directory. Each maze is a grid of pixels which has a black border running around the edge. The black border is interrupted at the top and bottom, which is the start and exit points. Select a maze and click OK, then hit run. The solver will generate a blue path between the start and end nodes.

### How it works
 For each maze, the solver makes a one-pass sweep of the maze to create a node tree, using a set of rules to determine whether a node is required for any given pixel. If a node is required, an object is created with a north east west and south connection. These connections are then connected to the adjacent nodes as the algorithm passes through the maze. Once the maze is analyzed, a depth-first search similar to Djikstra's algorithm is used to find the shortest path.

## Built With

* [Qt](http://www.qt.io) - Graphical Framework
* [Ubuntu](https://ubuntu.com/) - OS of choice

## Authors

* **Romain Astié** - [site](http://romain.astie.com)

## License

This project is licensed under the LGPLv3 License
## Acknowledgments

* Dr. Mike Pound/Computerphile/Brady Haran
* Pavel Strakhov on StackOverflow

