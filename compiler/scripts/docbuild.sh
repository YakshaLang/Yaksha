#!/usr/bin/env bash
echo -------------
echo Building docs
echo -------------
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
cd /runtime
codedoc /output/runtime.xml *.c *.h > /output/runtime.html
echo -------------
echo Docs built
echo -------------