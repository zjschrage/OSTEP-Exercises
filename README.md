# OSTEP-Exercises
Three Easy Pieces Problem Sets

# Structure
Folders are numbered by Piece_Chapter_Name where Piece is one of the three OS pieces the book details (virtualization, concurrency, persistence), Chapter is the chapter that the piece is divided into, and Name is the name of the chapter.

Within each folder, the set of problems will be completed in a c file titled p(Number) where Number is the problem number. Other common utils will exist in header files and included in these c files

# Compilation
Run `make` inside of a problem set folder. This will create a subfolder called bin where all of the binary executables will be compiled to. For each problem p1.c p2.c ... there will be a corresponding executable that can be run with `./bin/p1` `./bin/p2` ...