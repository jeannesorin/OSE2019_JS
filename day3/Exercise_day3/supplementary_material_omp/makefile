####################################################################### 

all: BS.exec dot_prod.exec normalize_vec.exec serial_pi.exec

####################################################################### 

## BC
BS.exec: BS.cpp
	g++ BS.cpp -fopenmp -o BS.exec      

## dot_prod
dot_prod.exec: dot_prod.cpp
	g++ dot_prod.cpp -fopenmp -o dot_prod.exec

## normalize vec
normalize_vec.exec: normalize_vec.cpp
	g++ normalize_vec.cpp -fopenmp -o normalize_vec.exec

## serial pi
serial_pi.exec: serial_pi.cpp
	g++ serial_pi.cpp -fopenmp -o serial_pi.exec

clean:
	rm -f *.exec
