# verletEngine - simple physics engine
[2024-05-19 19-46-31.webm](https://github.com/jbakowski/verletEngine/assets/96252496/287d5c4a-a0a3-4fea-a919-1ac60b4ccea4)
### How to build and run the project?

You will need to install CMake.

Enter the build directory and configure the project.

```
cd build
cmake ..
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

Currently supported features:
- gravity
- air resistance
- static, immovable, objects
- links - objects that try to stay in a certain distance from each other
