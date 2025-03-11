# 🟦 Squares Intersection Project 🟦

This project provides a **Bazel-based C++ implementation** for detecting **square intersections**, along with a **Dockerized environment** for easy building and testing.
Here you can find library **square_intersection_lib** in ```bazel-bin/src/``` and also application called **square_intersection**.

### **Build the Docker Image**

Before building a docker container, you need to create a .cache directory at ```/workspaces/.cache```
```sh
mkdir -m a=rwx -p /workspaces/.cache 
```
> **Please be careful with the permissions to the directory, you need to have the write permission flag in this directory.**

To build the project inside a **Docker container**, run the following command:
```sh
docker build --build-arg USERID=YOUR_USER_ID --build-arg GROUPID=YOUR_GROUP_ID -t squares_intersection .
```
Replace ```YOUR_USER_ID``` and ```YOUR_GROUP_ID``` with your actual user and group IDs.

This will install dependencies, fetch Bazel packages.
The build process is defined in the Dockerfile.

### **Run the container**

Once the build is complete, you can run Docker container:
```sh
docker run -v /workspaces/SquaresTutorial:/workspaces/SquaresTutorial -v /workspaces/.cache:/workspaces/.cache --rm -it --entrypoint /bin/bash squares_intersection
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
> test_process_intersections.robot literally explain how square_intersection application works. It means that in this tests you can find out the behaviour of app. How you can use it and how it works.
