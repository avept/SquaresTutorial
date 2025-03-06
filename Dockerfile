FROM ubuntu:22.04

RUN apt update && apt install -y \
    curl gnupg git unzip zip build-essential python3 python3-distutils \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg \
    && mv bazel.gpg /etc/apt/trusted.gpg.d/ \
    && echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list \
    && apt update && apt install -y bazel

RUN groupadd -g 1000 user && \
    useradd -m -u 1000 -g 1000 -s /bin/bash user

ENV USER_DIR=/home/user
ENV REPOSITORY_DIR=/workspaces/SquareTutorial
ENV BAZEL_OPTS="--enable_workspace=true --noenable_bzlmod"
ENV BAZEL_CACHE_DIR=$REPOSITORY_DIR/.cache/bazel

RUN mkdir -p $REPOSITORY_DIR && \
    chown -R user:user $REPOSITORY_DIR

USER user

WORKDIR $REPOSITORY_DIR
