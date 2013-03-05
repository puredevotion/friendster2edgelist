WHATCH OUT!
===========================
This is under heavy development. It only works when you place the files in dedicated directories. Please use at your own risk!

Friendster 2 Edgelist
===========================

This is a simple application written for Windows, Mac OSX and Solaris SPARC to convert Friendster .txt files to Edgelists for use in R.

Friendster .txt files
---------------------------

With the death of Friendster, the Archive Team has copied all friendster friend-lists and made available to the public through the Internet Archive in a series of text files.
These can be found here: http://archive.org/details/friendster-dataset-201107
However, these files are hard to analyse for academic purposes in its current format. Therefore I have written this application to convert the current format to edgelist files

Edgelist Files
--------------------------

Edgelist files are files in the Edgelist format (node, edge) as used by the statistical computing software R. Many packages in R can handle edgelist files, such as _sna_, _igraph_ and _SIENNA_.

Used Packages
---------------------------

This program is written in C++, using OpenMP for parallelization. I have tried to write the majority of the code independently from OS's, but some stuff i just easier in some platforms :)
Bear with me, this is my first real C++ project.

{todo: list of all libraries here}

Testing
----------------------------
I've tested all the code on OS X Lion, Windows 7, and Sun SPARC Solaris 4. (sorry, old server.)
