#!/bin/bash

FILE_NAME=$1
PORT=12345

qemu-arm -g $PORT $FILE_NAME &
