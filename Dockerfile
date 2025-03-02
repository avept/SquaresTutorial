FROM ubuntu:22.04

RUN apt update && apt install -y \
    curl gnupg git unzip zip build-essential python3 python3-distutils \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg \
    && mv bazel.gpg /etc/apt/trusted.gpg.d/ \
    && echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list \
    && apt update && apt install -y bazel

WORKDIR /app

ENV BAZEL_OPTS="--enable_workspace=true"

COPY . .

RUN bazel build $BAZEL_OPTS //...

CMD ["bazel", "run", "--enable_workspace=true", "//tests:square_intersection_tests", "--test_output=all"]
