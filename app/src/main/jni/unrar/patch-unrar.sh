#!/usr/bin/env bash

PATCH_PATH=$1
patch -Np1 --ignore-whitespace < $PATCH_PATH
grep -l -r 'abort()' * | xargs sed -i 's/abort(/abort(/g'
grep -l -r 'abort();/g'
