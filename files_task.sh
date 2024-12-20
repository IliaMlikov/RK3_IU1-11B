#!/bin/bash


if [ $# -ne 2 ]; then
    echo "Пожалуйста, укажите директорию и расширение файлов."
    exit 1
fi

DIRECTORY=$1
EXTENSION=$2

if [ ! -d "$DIRECTORY" ]; then
    echo "Директория не найдена."
    exit 1
fi

FILES=$(find "$DIRECTORY" -type f -name "*.$EXTENSION")
if [ -z "$FILES" ]; then
    echo "Файлы с расширением $EXTENSION не найдены."
else
    echo "Найденные файлы с расширением $EXTENSION:"
    echo "$FILES"
fi