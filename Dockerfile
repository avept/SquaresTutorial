FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive
ARG BAZEL_VERSION=6.3.2
ARG GROUPID=1001
ARG USERID=1001

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

RUN wget -q https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/bazel-${BAZEL_VERSION}-linux-x86_64 \
    && chmod +x bazel-${BAZEL_VERSION}-linux-x86_64 \
    && mv bazel-${BAZEL_VERSION}-linux-x86_64 /usr/local/bin/bazel

RUN pip install --no-cache-dir robotframework robotframework-requests

RUN groupadd -g ${GROUPID} user && \
    useradd -m -u ${USERID} -g ${GROUPID} -s /bin/bash user

ENV USER_DIR=/home/user
ENV WORKSPACE_DIR=/workspaces
ENV REPOSITORY_DIR=/workspaces/SquaresTutorial
ENV BAZEL_CACHE_DIR=$WORKSPACE_DIR/.cache
ENV PYTHONPATH=$REPOSITORY_DIR/robot

RUN mkdir -m a=rwx -p $REPOSITORY_DIR && \
    mkdir -m a=rwx -p $BAZEL_CACHE_DIR && \
    chown -R user:user $REPOSITORY_DIR && \
    chown -R user:user $BAZEL_CACHE_DIR

USER user

WORKDIR $REPOSITORY_DIR

VOLUME [$REPOSITORY_DIR]
VOLUME [$BAZEL_CACHE_DIR]
