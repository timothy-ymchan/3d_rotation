		=========================================
					   HOW TO USE:
		=========================================

1. In a terminal, navigate to the directory containing the file "3d_rotation.exe"

2. Enter "3d_rotation <path of shape file>" to open the simulation

----------------------------------------------------------------------------------------------------

		=========================================
			HOW TO CREATE SHAPE FILE:
		=========================================

Shape file is a textfile that contains information of the shape to be displayed.

A shape file contains two section: 

	POINTS, LINES

which define the points and lines to be displayed respectively.

The overall structure of a shape file looks like this:

	POINTS
	//Declaration of Points
	LINES
	//Declaration of Lines

Note that there label LINES must follow the last point declaration IMMEDIATELY,for example in file "shapes/cube.txt":

	....
	-1,1,-1 		<-This is the last point
	LINES			<-Immediately after it is the label LINES

-------------------------------------------------------------------------------------------------

  FORMAT OF DECLARING POINTS

	  x_coord,y_coord,z_coord

  For example, in file "shapes/cube.txt"

	  1,1,1

  Declares a point that is located on (1,1,1) 

--------------------------------------------------------------------------------------------------

  FORMAT OF DECLARING LINES

	  from_i_th_point, to_j_th_point

  For example, in file "shapes/cube.txt"

	  0,1

  Declares a lines that connect the 0th point to the 1st point, which is (1,1,1) and (1,-1,1)

