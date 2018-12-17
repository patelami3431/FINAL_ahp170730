q1:q1.c
	gcc -I$$HOME/local/gsl-2.5/include q1.c -lm -lgsl -lgslcblas -L$$HOME/local/gsl-2.5/lib -o q1
timepoints:timepoints.c
	gcc -I$$HOME/local/gsl-2.5/include timepoints.c -lm -lgsl -lgslcblas -L$$HOME/local/gsl-2.5/lib -o timepoints
.PHONY: clean
clean: 
	rm -f timepoints
	rm -f q1
