# Audio-Processing-Library-
An audio processing library to distinguish between 12 keywords 
-------- SELF PROJECT ------------

- HERE WE HAVE USED OPENBLAS LIBRARY FOR COMUTATION PURPOSE IN ROW FASHIONED MANNER
- ALSO WE HAVE ONE MORE CHANGE AND HAVE USED POINTER TO ARRAYS INSTEAD OF VECTORS WHICH WE USED IN TASK 2 OF THE ASSIGNMENT

- FUNCTIONS DEFINED IN Main.cpp -- 
-  Here the function open_multiply takes the input input matrix weight matrix and bias matrix and computes the product of input and weight matrix and adds bais matrix to it and updates the result matrix passed to it as an argument 
- Here the function takeInput1 takes the input from input file in which the float numbers are separated by a single space and stores then in an array in row fashioned form
- Here the function takeInput2 takes the input from weight1.txt, weight2.txt, weight3.txt, bias1.txt, bias2.txt, bias3.txt and strores them in array
- Softmax and relu fuctions defined compute the probabilty as defined in guidelines and make negative term zero repectively.
- Here the function topthree takes a input file inputstr,  pred array and anserr array and returns nothing. Computes the top three words with highest probabilities and updates the pred array as ruled by guidelines.
- Finally the libaudioPI function takes the the file to be computed over and pred array and does the computations as defined in guidelines and computes relu fuction on matrixes  and applies softmax fuction to final 1*12 matrix.
- We finally call the topthree fucntion to find the words with highest probailities. 

- run.cpp --
- Here we first check if ./yourcode.out audiosamplefile outputfile.txt is passed correctly and there are no mismatch in number of argumrnts.
- Next we call the libaudioAPI fuction pass it the input file and pred array defined in the same section.
- finally we output the desired result using ofstream in the outputfile.txt

**- HOW TO RUN THE CODE -- 
- also in makefile use the path of directory.
- First type the command "make" in the terminal to comiple the code and make the executable yourcode.out 
- Now type the following commands to link the library and export it.

- LD_LIBRARY_PATH=/home/mehul/project3:$LD_LIBRARY_PATH
- export LD_LIBRARY_PATH=/home/mehul/project3:$LD_LIBRARY_PATH

- Here instead of /home/mehul/project3 use the path of directory in which the files are stored
- Now run the code for inputfile.txt and append result to outputfile.txt by using the command ./yourcode.out inputfile.txt outputfile.txt 
- If this is called again provided the outputfile remains same the result will be appended to new line of this file.
- Instead of inputfile.txt & outputfile.txt, complete filepath of their's can be used.
