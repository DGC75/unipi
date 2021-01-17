#!/bin/bash

FILE_NAME=$1
PORT=12345

gdb-multiarch -q --nh -ex "set architecture arm" -ex "file ${FILE_NAME}" -ex "target remote localhost:${PORT}"
