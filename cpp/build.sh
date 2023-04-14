#!/bin/bash
emcc  file_block.cpp file_block_digest.cpp sha1.cpp \
    -lembind \
    -o ../file_block.js \
    -sMODULARIZE \
    -s ENVIRONMENT=node \
    -s INITIAL_MEMORY=1073741824