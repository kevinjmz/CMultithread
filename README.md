# CMultithread
This program takes 2 parameters, indices and number of threads. 
Creates an array of size indices and divides those indices to calculate the average with the number of threads specified.

*Creates an Array A of the size specified by the user through the arguments
** Generates random numbers and enters them into the array
*** Generates splits on the array to be able to assign threads
**** Assigns each thread to compute an addition from the assigned indices
***** Uses mutex locks to avoid data corruption
****** Adds every addition, one by one
******* Divides by the number of indices to generate average 

