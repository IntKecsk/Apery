This program is a cross-platform application for generating Penrose tilings and simulating cellular automata (such as Conway's Game of Life of von Neumann's CA)

#### Currently implemented features
* Penrose rhomb tiling representation
* Penrose tiling generation using triple deflation
* Basic Penrose tiling rendering

#### Features to be implemented
* Penrose tiling generation using sextuple deflation
* Penrose tiling generation using De Bruijn's algebraic method
* Richer user interface
* Cellular automata simulation
* Support for kite and dart and pentagon Penrose tilings 

### Building
This program uses Qt5
You can get the latest version of Qt at http://download.qt.io/official_releases/qt/

After that, the program is built by `qmake && make && make install`
