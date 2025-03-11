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
bazel build //...
```

and run:

```sh
bazel run //tests:square_intersection_tests 
```

Moreover, you can run automated tests:
```sh
robot robot/test_process_intersections.robot
```