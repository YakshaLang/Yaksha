FROM ubuntu:latest
ENV DEBIAN_FRONTEND=noninteractive
# TODO do we even use clang? maybe we should use it in addition to gcc?
    # But at the moment this is useless
    # Perhaps we can remove clang-12 install here !
ARG CMAKE_VERSION=3.22.0
RUN apt-get update && apt-get -y -q install clang-12 git wget build-essential python3 libssl-dev lcov gcovr dos2unix

RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.tar.gz \
  && tar -zxf cmake-${CMAKE_VERSION}.tar.gz \
  && cd cmake-${CMAKE_VERSION} \
  && ./bootstrap \
  && make -j4 \
  && make install


RUN   ln -s /usr/bin/clang-12 /usr/bin/clang \
      && ln -s /usr/bin/clang++-12 /usr/bin/clang++


RUN apt-get -y -q install python3-pip && pip3 install tqdm

ADD src /app/src
ADD 3rd /app/3rd
ADD test_data /app/test_data
ADD tests /app/tests
ADD CMakeLists.txt /app/CMakeLists.txt
ADD scripts /app/scripts
ADD libs /app/libs
ADD runtime /app/runtime
ADD carpntr /app/carpntr
RUN mkdir "/app/bin"

ENTRYPOINT ["/app/scripts/code-coverage.sh"]
