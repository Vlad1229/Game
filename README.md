# Space Shooter game

A simple C++ game.

## Required software

- **Qt Software Development Kit**.
- **MinGW**.

## Descrition

### Main classes of the project:

1. MemoryPool: A class that stores allocated memory for temporary objects. This class is necessary because it uses the already allocated memory to place new objects in it, which saves the time required to access the memory to create and remove enemies that occur after a certain period of time throughout the game.
2. GameObject: A base class for al game objects;
3. Enemy: A base class for all classes of enemies, inherits the GameObject class;
4. Player: A class that describes player behavior;
5. Game: A class that creates game objects and monitors their state.

## Getting Started

Enter the project folder.

```
cd SpaceShooter
```

Create a project file.

```
qmake -project "QT += core gui" "QT += widgets"
```

Prepare project file for compilation.

```
qmake SpaceShooter.pro
```

Compile source code into an executable program.

```
mingw32-make
```

Start the application.

```
cd release
SpaceShooter.exe
```

## Screenshots

![1 screenshot](https://user-images.githubusercontent.com/31863793/64407083-21a57080-d08c-11e9-9b1c-896dba69c79d.png)

![2 screenshot](https://user-images.githubusercontent.com/31863793/64407118-33871380-d08c-11e9-88c9-8724fb68ca48.png)
