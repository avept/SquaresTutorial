FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    wget \
    curl \ 
    gnupg \
    git \
    unzip \ 
    zip \
    build-essential \
    python3 \
    python3-pip \
    python3-distutils \
    pkg-config \
    libopencv-core-dev \
    libopencv-highgui-dev \
    libopencv-calib3d-dev \
    libopencv-features2d-dev \
    libopencv-imgproc-dev \
    libopencv-video-dev \
    && rm -rf /var/lib/apt/lists/*

ARG BAZEL_VERSION=6.3.2
RUN wget -q https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/bazel-${BAZEL_VERSION}-linux-x86_64 \
    && chmod +x bazel-${BAZEL_VERSION}-linux-x86_64 \
    && mv bazel-${BAZEL_VERSION}-linux-x86_64 /usr/local/bin/bazel

RUN pip install --no-cache-dir robotframework robotframework-requests

RUN groupadd -g 1000 user && \
    useradd -m -u 1000 -g 1000 -s /bin/bash user

ENV USER_DIR=/home/user
ENV REPOSITORY_DIR=/workspaces/SquaresTutorial

ENV BAZEL_OPTS="--enable_workspace=true --noenable_bzlmod"
ENV BAZEL_CACHE_DIR=$REPOSITORY_DIR/.cache/bazel

RUN mkdir -p $REPOSITORY_DIR && \
    chown -R user:user $REPOSITORY_DIR

USER user

WORKDIR $REPOSITORY_DIR

VOLUME [$REPOSITORY_DIR]
