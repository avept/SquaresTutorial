cc_library(
    name = "opencv",
    hdrs = glob([
        "aarch64-linux-gnu/opencv4/opencv2/cvconfig.h",
        "arm-linux-gnueabihf/opencv4/opencv2/cvconfig.h",
        "x86_64-linux-gnu/opencv4/opencv2/cvconfig.h",
        "opencv4/opencv2/**/*.h*",
    ]),
    includes = [
        "aarch64-linux-gnu/opencv4/",
        "arm-linux-gnueabihf/opencv4/",
        "x86_64-linux-gnu/opencv4/",
        "opencv4/",
    ],
    linkopts = [
        "-l:libopencv_core.so",
        "-l:libopencv_calib3d.so",
        "-l:libopencv_features2d.so",
        "-l:libopencv_highgui.so",
        "-l:libopencv_imgcodecs.so",
        "-l:libopencv_imgproc.so",
        "-l:libopencv_video.so",
        "-l:libopencv_videoio.so",
    ],
    visibility = ["//visibility:public"],
)
