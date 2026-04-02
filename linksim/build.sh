#!/bin/bash
cmake -S. -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build -j
