CC = mpicc          # Change this to your MPI compiler (mpicc, mpic++, mpiCC, mpicxx, etc)
CFLAGS = -fopenmp   # The -fopenmp flag enables OpenMP
LIBS = -lm          # Include the math library

hdf5 =  -I/opt/homebrew/Cellar/hdf5/1.14.1/include -L/opt/homebrew/Cellar/hdf5/1.14.1/lib -lhdf5
FILES = allocate_3D_array.c deallocate_3D_array.c load_snapshot.c save_snapshot.c initialize.c one_timestep.c communicate_above_below.c

compile:
	${CC} ${CFLAGS} ${hdf5} -o main.o main.c ${FILES} ${LIBS}
execute:
	mpirun -np 4 ./main.o

all: compile execute
