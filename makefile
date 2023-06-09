CC = mpicc          # Change this to your MPI compiler (mpicc, mpic++, mpiCC, mpicxx, etc)
CFLAGS = -fopenmp   # The -fopenmp flag enables OpenMP
LIBS = -lm          # Include the math library

hdf5 =  -I/opt/homebrew/Cellar/hdf5/1.14.1/include -L/opt/homebrew/Cellar/hdf5/1.14.1/lib -lhdf5 # Location of my local hdf5 library
MEMORY_FILES = allocate_3D_array.c deallocate_3D_array.c
SNAPSHOT_FILES = load_snapshot.c save_snapshot.c
FILES = initialize.c one_timestep.c communicate_above_below.c

compile:
	${CC} ${CFLAGS} ${hdf5} -o main.o main.c ${FILES} ${SNAPSHOT_FILES} ${MEMORY_FILES} ${LIBS}
execute:
	mpirun -np 4 ./main.o

all: compile execute
