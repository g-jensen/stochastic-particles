#!/bin/bash

TEX_FILE="latex/particle_survival.tex"
OUTPUT_DIR="build/latex"


compile() {
  latexmk -output-directory=$OUTPUT_DIR -aux-directory=$OUTPUT_DIR $TEX_FILE 
}

watch() {
  echo "Watching $TEX_FILE for changes..."
  compile
  last_mod=$(stat -c %Y "$TEX_FILE")
  while true; do
    sleep 1
    current_mod=$(stat -c %Y "$TEX_FILE")
    if [ "$current_mod" != "$last_mod" ]; then
      echo "File changed, recompiling..."
      compile
      last_mod=$current_mod
    fi
  done
}

mkdir -p $OUTPUT_DIR

case "$1" in
  -w|--watch)
    watch
    ;;
  *)
    compile
    ;;
esac
