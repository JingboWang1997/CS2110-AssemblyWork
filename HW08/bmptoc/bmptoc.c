// bmptoc.c
// Name: YOUR NAME HERE

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// Your program will only support BMP files that
// have a max size that is equivalent to the size
// of the GBA screen.
#define MAX_BMP_FILE_SIZE (0x36 + 240 * 160 * 4)

//Function prototypes
unsigned int getWidth(char* bmp_contents);
unsigned int getHeight(char* bmp_contents);
void writeHFile(char* h_filename, unsigned int width, unsigned int height);
void writeCFile(char* h_filename, char* bmp_contents, unsigned int width, unsigned int height);
void readBMPFile(char* bmp_filename, char* bmp_contents);

int main(int argc, char *argv[]) {
// ========================================================
    // 1. Make sure the user passed in the correct number of arguments
    // Hint: You'll want to see what value argc has.
    if (argc != 2) {
        printf("Usage: %s <file>.bmp", argv[0]);
        return -1;
    }
// ========================================================
    // A couple of useful variables.
    // The name of the bmp file (Example: "diddy.bmp")
    char* bmp_filename = argv[1];
    // The length of the bmp file name ("diddy.bmp" --> 9)
    int bmp_filename_len = strlen(bmp_filename);
// ========================================================
    // Read the bmp file into the array bmp_contents
    char bmp_contents[MAX_BMP_FILE_SIZE];
    readBMPFile(bmp_filename, bmp_contents);
// ========================================================
    // 2. Get the width and height of the image. Read the BMP file format
    // to determine what you should do for this one. Then implement the
    // functions at the end of the file.
    unsigned int width = getWidth(bmp_contents);
    unsigned int height = getHeight(bmp_contents);
// ========================================================
    // 3. Create the header (.h) file.
    // We have done this for you as an example.
    
    // The filename of the .h file we want to create
    char h_filename[100];
    // Copy the bmp file name
    strcpy(h_filename, bmp_filename);
    // Set the character right after the '.' to 'h'
    // so diddy.bmp --> diddy.hmp
    h_filename[bmp_filename_len - 3] = 'h';
    // Add the null terminator right after the 'h'
    // diddy.hmp --> diddy.h
    h_filename[bmp_filename_len - 2] = 0;

    // Write all the relevant data to the .h file
    writeHFile(h_filename, width, height);
    
// ========================================================
    // 4. Create the C source file (.c)
    
    // The filename of the .c file we want to create
    char c_filename[100];
    // Copy the bmp file name
    strcpy(c_filename, bmp_filename);
    
    // Set the character right after the '.' to 'c'
    // so diddy.bmp --> diddy.cmp
    // YOUR CODE HERE

    // Add the null terminator right after the 'c'
    // diddy.cmp --> diddy.c
    // YOUR CODE HERE

    writeCFile(c_filename, bmp_contents, width, height);
    return 0;
}

/*
 *
 * Format of a bmp header (bmp_contents)
 * file offset  |   length   |     field
 * 0x12         |  4 bytes   |  image width
 * 0x16         |  4 bytes   |  image height
 *
 */

// TODO
// complete this function that uses the bmp bmp_contents to retrieve the width of
// the image
// HINT: this can be done in one line
unsigned int getWidth(char* bmp_contents) {
    // Silence unused arguments warning, remove this when you write your solution.
    bmp_contents[0] = bmp_contents[0]; 
    // YOUR CODE HERE
    return 0;
}

// TODO
// complete this function that uses the bmp bmp_contents to retrieve the height of
// the image
// HINT: this can be done in one line
unsigned int getHeight(char* bmp_contents) {
    // Silence unused arguments warning, remove this when you write your solution.
    bmp_contents[0] = bmp_contents[0]; 
    // YOUR CODE HERE
    return 0;
}

void writeHFile(char* h_filename, unsigned int width, unsigned int height) {
    // We've implemented outputing the header file correctly assuming your
    // getWidth and getHeight work properly. Read this code carefully and
    // read the man pages because you'll have to do something similar
    // for generating the C file.
    FILE* header_file = fopen(h_filename, "w");
    if (header_file == NULL) {
        printf("Error creating file %s: %s\n", h_filename, strerror(errno));
    }

    // Get just the basename portion of the header file.
    // Example: diddy.h --> diddy
    char basename[100];
    strcpy(basename, h_filename);
    int basename_len = strlen(h_filename) - 2;
    basename[basename_len] = 0;

    // Get a version of the basename where it is all upper case.
    // Example: diddy --> DIDDY
    char all_caps_basename[100];
    strcpy(all_caps_basename, basename);
    for (int i = 0; i < basename_len; i++) {
        all_caps_basename[i] = toupper(all_caps_basename[i]);
    }

    /* File format:
     *
     *  #define FILE_WIDTH 100
     *  #define FILE_HEIGHT 150
     *  const unsigned short file_data[15000];
     */
    // Note that 15000 in the above example is just 
    // 100 * 150 (width * height), not a magic number.

    fprintf(header_file, "#define %s_WIDTH %d\n", all_caps_basename, width);
    fprintf(header_file, "#define %s_HEIGHT %d\n", all_caps_basename, height);

    fprintf(header_file, "const unsigned short %s_data[%d];\n", basename, width * height);

    fclose(header_file);
}

void writeCFile(char* c_filename, char* bmp_contents, unsigned int width, unsigned int height) {
    // Now you are responsible for creating a c file with the same basename
    // as the bmp file that was passed in file.bmp -> file.c
    // Hint: Use the code in writeHFile as a guide for how to
    //       initialize the filename and  open the file.

    printf("printf(%s, bmp start addr %p, width %d, height %d", c_filename, bmp_contents, width, height);


    /* File format:
     *
     *  const unsigned short file_data[15000] = {
     *    0x4521, 0x5B2F, 0x1F69, ...
     *  };
     */
// ========================================================
    // 1. Open the file
    // YOUR CODE HERE
// ========================================================

    // 2. You must output the first part of the C file which will look like the
    // line above. Note that instead of 15000 you will have the width * height.
    // Hint: Look at how fprintf is used elsewhere in this code and read the
    //       man page.
    //

    // Get just the basename portion of the c file.
    // Example: diddy.c --> diddy
    // YOUR CODE HERE

// ========================================================
    // 3. Iterate over the pixel data convert it to hex and write the output to the C file.
    // Hint: Pay careful attention to the format of the BMP file. It is stored
    // in reverse order.

    // Useful variables:
    // bmp_contents - array of bytes that contains all the data in the bmp file
    // height/width - self explanatory, just so you're aware they're there
    // YOUR CODE HERE
// ========================================================
    // 4. Finally write the closing brace and semicolon to the file and
    // close the file.
    // YOUR CODE HERE
}

// Reads the contents of the file bmp_filename into bmp_contents.
void readBMPFile(char* bmp_filename, char* bmp_contents) {
    FILE* bmp_file = fopen(bmp_filename, "r");
    if (bmp_file == NULL) {
        printf("BMP file (%s) not found.", bmp_filename);
    }
    int success = fread(bmp_contents, 1, MAX_BMP_FILE_SIZE, bmp_file);
    if (success) {
        fclose(bmp_file);
    } else {
        printf("Could not read BMP file.\n");
    }
}
