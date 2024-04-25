FROM ubuntu:noble-20240407.1
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get -y -q install curl git wget build-essential python3 libssl-dev gcc build-essential cmake ninja-build pkg-config

RUN mkdir /workspace
WORKDIR /workspace
RUN git clone https://github.com/madler/zlib.git && cd zlib && ./configure && make && make install
RUN git clone https://github.com/michaelrsweet/mxml.git && cd mxml && ./configure && make && make install
RUN export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib && git clone https://github.com/michaelrsweet/codedoc.git && cd codedoc && ./configure && make && make install
RUN rm -rf zlib mxml codedoc

# Mounts
# /runtime << where our code is in
# /output << where the docs will be

ADD scripts/docbuild.sh /workspace/docbuild.sh
RUN chmod +x /workspace/docbuild.sh

ENTRYPOINT ["/workspace/docbuild.sh"]