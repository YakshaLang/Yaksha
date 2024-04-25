FROM ubuntu:noble-20240407.1
ENV DEBIAN_FRONTEND=noninteractive
ARG ZIG_VERSION=0.9.1
RUN apt-get update && apt-get -y -q install clang-12 clang-tools git wget build-essential python3 libssl-dev lcov gcovr dos2unix cmake ninja-build

RUN   ln -s /usr/bin/clang-12 /usr/bin/clang \
      && ln -s /usr/bin/clang++-12 /usr/bin/clang++

RUN apt-get -y -q install python3-pip && pip3 install tqdm

RUN wget https://ziglang.org/download/0.9.1/zig-linux-x86_64-${ZIG_VERSION}.tar.xz \
    && tar -xf zig-linux-x86_64-${ZIG_VERSION}.tar.xz \
    && mv zig-linux-x86_64-${ZIG_VERSION} zig

ENV PATH="${PATH}:/zig"

ADD src /app/src
ADD 3rd /app/3rd
ADD test_data /app/test_data
ADD tests /app/tests
ADD CMakeLists.txt /app/CMakeLists.txt
ADD scripts /app/scripts
ADD libs /app/libs
ADD runtime /app/runtime
ADD carpntr /app/carpntr
ADD test_libs /app/test_libs
ADD bin/test.txt /app/test.txt
RUN mkdir "/app/bin"
RUN dos2unix /app/scripts/*.py
RUN dos2unix /app/scripts/*.sh

ENTRYPOINT ["/app/scripts/code-coverage.sh"]
