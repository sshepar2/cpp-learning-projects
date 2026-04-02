#!/bin/bash
cppcheck --project=build/compile_commands.json --suppress=missingIncludeSystem
