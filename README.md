# Dissertation
A program that will accept an image, embed data into it and after compression, will return the data.

The menu system will allow you:
	   1. to create BMPs 
	   2. import a bmp from a list of samples or one that you have created
	   3. Embed a message into a bmp (choose from a selction of messages) - please note that the program will exit if
	      the message size is too large for the image.
	   4. Convert the image into a JPEG
	   5. Decode the message out of the JPEG
     
	   Notes -
	   If you see the main menu after completing an operation, it means that it completed successfully
	   When creating/embedding an image, dimensions of 512x512 work best in relation to creation speed and storage size
	   
	   Check the project directory after creation to see your new image
	   When selecting an image to import, the program will read the contents of both the project directory and a directory in the
	   solution folder called 'ImageSamples', and present you with a list of all of these to choose from.
	   Because the message is being stored in the top line of the image, if you create a BMP with small dimensions, say 32x32,
	   and then try to put a large message inside the program, it will lead to an exception.
	   Lastly, when selecting a JPEG to decode, ensure that you choose the filename that you created but with the '.jpg' extension.

