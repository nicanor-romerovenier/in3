#!/bin/sh

if [ -z "$1" ]; then
    SERIAL_PORT=ttyACM0
else
    SERIAL_PORT=$1
fi

echo "Using serial port $SERIAL_PORT"

if [ -z "${ARDUINO_SKETCH_DIR}" ]; then
  echo "ARDUINO_SKETCH_DIR is undefined. Example: $ export ARDUINO_SKETCH_DIR=/home/user/Arduino/"
  exit 1
else
  echo "ARDUINO_SKETCH_DIR=${ARDUINO_SKETCH_DIR}"
fi

$ARDUINO_SKETCH_DIR/hardware/STM32/tools/linux/maple_upload $SERIAL_PORT 1 1EAF:0003 $PWD/build/IN3_FW.cpp.bin
