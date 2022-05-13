#!/bin/sh
set -ex
test -d Build || mkdir -p Build
cd Build
cmake ../Projects -DCMAKE_BUILD_TYPE=Release -DENABLE_RAD_TELEMETRY=OFF -DBUILD_OGDA=OFF -DAUX_DATA=/usr/pkg/share/overgrowth
make -j4
