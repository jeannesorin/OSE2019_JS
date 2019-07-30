
### Fortran compiler wrapper
### FC=mpif90

### CPP compiler wrapper
CXX=mpicxx

### Optimization flags
FFLAGS=-O3 -fopenmp

#######################################################################	

all: pi_hybrid.exec
 
#######################################################################	

## Example 1
pi_hybrid.exec: pi_hybrid.cpp
	$(CXX) $(FFLAGS) pi_hybrid.cpp -o pi_hybrid.exec


#######################################################################	

clean :
	rm -f *.exec

#######################################################################	
