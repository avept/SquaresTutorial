# 🟦 Squares Intersection Project 🟦

This project provides a **Bazel-based C++ implementation** for detecting **square intersections**, along with a **Dockerized environment** for easy building and testing.

### **Build the Docker Image**
To build the project inside a **Docker container**, run the following command:
```sh
docker build -t squares_intersection .
```

This will install dependencies, fetch Bazel packages, and compile the project inside a container.
The build process is defined in the Dockerfile.

### **Run the Program**

Once the build is complete, run the executable inside Docker:
```sh
docker run -v $(pwd)/bazel-cache:/home/myuser/squares/.cache/bazel -it --entrypoint /bin/bash squares_intersection
```
