#!/bin/bash

FILE_NAME=$1

arm-linux-gnueabihf-gcc $FILE_NAME -mfpu=neon -static -ggdb3

