# verletEngine - simple physics engine
### How to build and run the project?

You will need to install CMake and VCPKG.

Enter the build directory and configure the project.

```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
```

Build the project.
```
cmake --build .
```

By default, on Windows, the project will be built in `debug`. If you want to build
in release, use this command instead:
```
cmake --build . --config Release
```

Run the project by running the created executable, which is in the `bin` directory
of the build directory.

### General

verletEngine utilizes Verlet's integration, which is a method used to perform discrete integration
of Newton's equations of motion.

This project uses SFML 2.6 to render the graphics.

Currently supported features:
- gravity
- air resistance
- linear and angular dynamics
- friction
- static, immovable, objects
- links - objects that try to stay in a certain distance from each other
