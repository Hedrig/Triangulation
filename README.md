# BarrelMesh
This is one of the many test tasks I'm doing as of late. This one performs simple triangulation on a given cloud of 3D points.

## Command line arguments
-i | --input <path> - specifies path to the input file containing the cloud of points. Points should each take a new line, specifying their index and X, Y, Z coordinates. The file is permitted to have comments: they are to be preceded with an asterisk (*).

-o | --output <path> - specifies path to the output file. It would be created if missing. Note: I didn't check if the algorithm replaces the old file or writes to the end of it, so be careful while testing the application of the same file. 
