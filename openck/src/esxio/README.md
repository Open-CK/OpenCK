#esxio/

Contains the files needed for performing input/ouput operations on .es(x) files:
This includes form definitions, data read/write methods, and a form factory class.

###[name]form.cpp/h

Source/header files that define the layout and read/write behaviour of form objects, 
created from record structures in the game files.

###formfactory.cpp/h

Code that allows the generation of form objects in the fileread/filewrite objects.

###fileread/filewrite.cpp/h

Contains methods to handle input and output of .es(x) files.