FROM ubuntu:21.04
ENV DEBIAN_FRONTEND=noninteractive
# TODO do we even use clang? maybe we should use it in addition to gcc?
    # But at the moment this is useless
    # Perhaps we can remove clang-12 install here !
ARG CMAKE_VERSION=3.22.0
RUN apt-get update && apt-get -y -q install clang-12 git wget build-essential python3 \
      && wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /opt/cmake \
      && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake/ \
      && rm /tmp/cmake-install.sh

RUN   ln -s /opt/cmake/bin/cmake /usr/bin/cmake \
      && ln -s /usr/bin/clang-12 /usr/bin/clang \
      && ln -s /usr/bin/clang++-12 /usr/bin/clang++

RUN  apt-get install -y lcov gcovr dos2unix

ADD src /app/src
ADD 3rd /app/3rd
ADD test_data /app/test_data
ADD tests /app/tests
ADD CMakeLists.txt /app/CMakeLists.txt
ADD scripts /app/scripts
RUN mkdir "/app/bin"

ENTRYPOINT ["/app/scripts/code-coverage.sh"]
