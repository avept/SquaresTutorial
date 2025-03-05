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
    "-l:libopencv_cudaimgproc.so",
    "-l:libopencv_imgcodecs.so",
    "-l:libopencv_tracking.so",
    "-l:libopencv_calib3d.so",
]

LINKOPT = lib_paths + opencv_lib 

cc_library(
    name = "square_intersection",
    srcs = ["square.h", "square.cpp"], 
    linkopts = LINKOPT,
    deps = ["@linux_opencv//:opencv"],
    visibility = ["//visibility:public"],
)
