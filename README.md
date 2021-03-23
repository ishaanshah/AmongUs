# Assignment 0

#### Roll No - 2019111028

## Steps to run

- Create a directory `libraries` and put source code for `GLFW`, `GLAD` and `GLM`
  in `libraries/glfw`, `libraries/glad` and `libraries/glm` respectively.
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
./assign0 1
./assign0 2
./assign0 3
```

**Note** - The command line argument denotes the shape to be loaded

1. Hexagonal Dipyramid
2. Decagonal Prism
3. Undecagonal Pyramid

## Controls

- **1:** Front View
- **2:** Side View
- **3:** Angle View
- **Space:** Toggle object rotation (about z-axis)
- **Shift+Space:** Toggle camera rotation (about y-axis with object coordinates
  as center)
- **X:** Move object along +x axis
- **Y:** Move object along +y axis
- **Z:** Move object along +z axis
- **Shift+X:** Move object along -x axis
- **Shift+Y:** Move object along -y axis
- **Shift+Z:** Move object along -z axis
- **U:** Move camera along +x axis
- **V:** Move camera along +y axis
- **W:** Move camera along +z axis
- **Shift+U:** Move camera along -x axis
- **Shift+V:** Move camera along -y axis
- **Shift+W:** Move camera along -z axis
