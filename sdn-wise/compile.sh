#!/bin/bash
TARGET="sky"

echo "*** COMPILING... ***"
echo "> Compile controller"
make TARGET=$TARGET clean && make TARGET=$TARGET SINK=1 "$@"
mv sdn-wise.$TARGET ./sink/sink.$TARGET
make TARGET=$TARGET clean && make TARGET=$TARGET SINK=0 "$@"
mv sdn-wise.$TARGET ./node/node.$TARGET
make TARGET=$TARGET clean
echo "*** FINISHED! ***"
