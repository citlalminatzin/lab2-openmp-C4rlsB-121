#!/bin/bash
EXECUTABLE_NAME="holaMundo"
FILE_NAME="holaMundo.c"
NUM_THREADS=(1 2 4 6 8)

EXECUTABLE_PATH="./$EXECUTABLE_NAME"
FILE_PATH="./$FILE_NAME"

ejecutar() {
        for hilos in "${NUM_THREADS[@]}"
        do
                echo "---------------------------------------------------------"
                export OMP_NUM_THREADS=$hilos
                "$EXECUTABLE_PATH"
        done
}


if [ -x "$EXECUTABLE_PATH" ]; then
        ejecutar

elif [ -f "$FILE_NAME" ]; then
        gcc "$FILE_NAME" -o "$EXECUTABLE_NAME" -fopenmp
        ejecutar
else
        echo "No hay ejecutable ni archivo de codigo disponible"
fi

