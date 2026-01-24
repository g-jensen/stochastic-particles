#!/bin/bash

OUTPUT_DIR="build/latex"

mkdir -p $OUTPUT_DIR

latexmk -output-directory=$OUTPUT_DIR -aux-directory=$OUTPUT_DIR -silent "$1"