# Overview
An example of docker ignore that you can visualise. 

# Instructions
* Run `docker build .` and observe the small context sent to the docker daemon.
* Create a 1G file with `head -n 1G < /dev/urandom > ignoreme`. 
* Run `docker build .` and observe the, larger context sent to the daemon.
* Rename .dockerignore.example to .dockerignore.
* Run `docker build .` and observe the same context size as in the first step. 
