lib_paths = [
    "-L/usr/local/lib",
    "-L/usr/lib/x86_64-linux-gnu/",
]

opencv_lib = [
    "-l:libopencv_core.so",
    "-l:libopencv_highgui.so",
    "-l:libopencv_imgproc.so",
    "-l:libopencv_video.so",
    "-l:libopencv_videoio.so",
    "-l:libopencv_imgcodecs.so",
]

LINKOPT = lib_paths + opencv_lib 

cc_library(
    name = "square_intersection_lib",
    srcs = ["square.cpp"],
    hdrs = ["square.h"],
    copts = ["-I/usr/include/opencv4"],
    linkopts = LINKOPT,
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "square_intersection",
    srcs = ["main.cpp"],
    deps = [
        "//src:square_intersection_lib"
    ],
    copts = ["-I/usr/include/opencv4"],
    linkopts = LINKOPT,
    visibility = ["//visibility:public"]
)
