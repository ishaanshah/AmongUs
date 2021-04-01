# Assignment 1

#### Roll No - 2019111028

## Steps to run

- Create a directory `lib` and put source code for `GLFW`, `GLAD` and `GLM`
  in `lib/glfw`, `lib/glad` and `lib/glm` respectively.
- Install `Freetype` library using package manager for your distribution.
- Create a directory `build` and generate `Makefile` using -

```bash
mkdir build
cd build
cmake ..
```

- Compile the program by running -

```bash
make
```

- Execute the program using -

```bash
./AmongUs
```

## Controls

- **W:** Move Up
- **A:** Move Left
- **S:** Move Down
- **D:** Move Right
- **Space:** Toggle lights (Hold)
