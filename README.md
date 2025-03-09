# 🟦 Squares Intersection Project 🟦

This project provides a **Bazel-based C++ implementation** for detecting **square intersections**, along with a **Dockerized environment** for easy building and testing.

### **Build the Docker Image**
To build the project inside a **Docker container**, run the following command:
```sh
docker build -t squares_intersection .
```

This will install dependencies, fetch Bazel packages.
The build process is defined in the Dockerfile.

### **Run the container**

Once the build is complete, run the executable inside Docker:
```sh
docker run -v /workspaces/SquaresTutorial:/workspaces/SquaresTutorial --rm -it --entrypoint /bin/bash squares_intersection
```

## **Build and run the project**

Once we are inside the container, we can build the project itself:
```sh
bazel build --enable_workspace=true //...
```

and run:

```sh
bazel run --enable_workspace=true //tests:square_intersection_tests 
```