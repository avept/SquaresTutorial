FROM ubuntu:22.04

RUN apt update && apt install -y \
    curl gnupg git unzip zip build-essential python3 python3-distutils \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg \
    && mv bazel.gpg /etc/apt/trusted.gpg.d/ \
    && echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list \
    && apt update && apt install -y bazel

RUN groupadd -g 1000 myuser && \
    useradd -m -u 1000 -g 1000 -s /bin/bash myuser

USER myuser

RUN mkdir -p /home/myuser/squares

WORKDIR /home/myuser/squares

ENV BAZEL_OPTS="--enable_workspace=true --noenable_bzlmod"
ENV BAZEL_CACHE_DIR=/home/myuser/squares/.cache/bazel

RUN mkdir -p $BAZEL_CACHE_DIR

# Squares_intersect project
COPY src /home/myuser/squares/src
COPY tests /home/myuser/squares/tests
COPY WORKSPACE /home/myuser/squares/WORKSPACE
COPY README.md /home/myuser/squares/README.md

RUN bazel build $BAZEL_OPTS //...

CMD ["bazel", "run", "--enable_workspace=true", "//tests:square_intersection_tests", "--test_output=all"]