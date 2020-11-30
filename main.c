// You will need an identical  array to use to hold
// the output of your image transformation
//*** ????????????????????????????????

// ME DEFINING THEIMAGEARRAY

int theImageArray[1025][MAX_WIDTH];
int theImageArrayDup[1025][MAX_WIDTH];

// Internal function to read the header information
// stored at the beginning of a PGM format file.
//
// Used by read_pgm_file_into_array to see set the
// height and width of the image
FILE* read_pgm_file_info
(
    int* height,    // output
    int* width,    // output
    int* maxPixel,  // output
    char* pgmFname   // input
)
{
    static FILE* fp = 0L ;
    char pgmFormatFlag[3] =  { '\0' } ;

    char trash[80] = { '\0' } ;
    memset ( ( void * ) trash, '\0', 80 ) ;

    fp = fopen ( pgmFname, "r" ) ;

    if ( fp )
    {
        // Check the signature
        fscanf ( fp, "%2c\n", pgmFormatFlag ) ;
        //printf ( "%s\n", pgmFormatFlag ) ;
        if ( ! strcmp ( pgmFormatFlag, "P2" ) )
        {
            // Skip the comment line
            //fscanf ( fp, "\n" ) ;
            fgets (  trash, 70, fp ) ;
            //printf ( "%s", trash ) ;

            // Read the width
            fscanf ( fp, "%i", width ) ;
            //printf ( "%i,", *width ) ;

            // Read the height
            fscanf ( fp, "%i", height ) ;
            //printf ( "%i\n", *height ) ;

            // Read the maximum pixel value
            fscanf ( fp, "%i", maxPixel ) ;
        }
        //fclose ( fp ) ;
    }


    return fp ;
}

// Write out an array as a PGM file (ascii).
// writes imageArray to the file named by pgmOutFileName.
// commentLine, height, width, and maxPixel must be
// set and passed to this function so they can
// be written correctly in the PGM file header and
// so this function will know how many rows (image height)
// and how many columns (image width) to write.
void write_pgm_file_from_array
(
    char* pgmOutFileName,     // input
    int imageArray[][MAX_WIDTH], // input
    char* commentLine,      // input
    int height,          // input
    int width,          // input
    int maxPixel         // input
)
{
    int row = 0 ;
    int col = 0 ;
    FILE* fp = fopen ( pgmOutFileName, "w" ) ;
    if ( fp )
    {
        // Generate the header info
        fprintf ( fp, "P2\n" ) ;
        fprintf ( fp, "%s\n", commentLine ) ;
        fprintf ( fp, "%u %u\n", width, height ) ;
        fprintf ( fp, "%u\n", maxPixel ) ;

        // Now write out the data, ensuring that at most 70
        // values appear on each line, even if width is > 70
        for ( row = 0 ; row < height ; row ++ )
        {
            for ( col = 0 ; col < width ; col ++ )
            {
                fprintf ( fp, "%u", imageArray[row][col] ) ;
                // break up long rows into multiple lines as needed
                if ( MAX_PIXELS_PER_LINE > 1 )
                {
                    fprintf ( fp, " " ) ;
                }
                if ( ( col % MAX_PIXELS_PER_LINE ) == 0 )
                {
                    fprintf ( fp, "\n" ) ;
                }
            }
            // Watch out of special case of width == 70
            if ( col % MAX_PIXELS_PER_LINE )
            {
                fprintf ( fp, "\n" ) ;
            }
        }
        fclose ( fp ) ;
    }
    return ;
}

// Read file named by pgmInFileName argument into
// the array imageArray. This function respects the
// MAX_HEIGHT and MAX_WIDTH values, so if you declare
// your target array using these bounds, even reading
// a large image file should not blow up your program.
// (but you will only get the upper left-hand corner
// of the image).  Checks that the file read is a PGM
// (gray scale, ascii) file.
//
// Sets height, width, and maxPixel according to the
// header read.
void read_pgm_file_into_array
(
    int imageArray[][MAX_WIDTH],          // output
    int* height,        // output
    int* width,        // output
    int* maxPixel,              // output
    char* pgmInFileName      // input
)
{
    int row = 0 ;
    int col = 0 ;
    FILE* fp = read_pgm_file_info ( height, width, maxPixel, pgmInFileName ) ;
    char trash = ' ';
    char yesThreshold = ' ';

    if ( fp )
    {
        printf ( "reading height=%d, width=%d\n", *height, *width ) ;
        for ( row = 0 ; row < MIN( MAX_HEIGHT - 1, *height ) ; row ++ )
        {
            for ( col = 0 ; col < MIN( MAX_WIDTH -1, *width ) ; col ++ )
            {
                fscanf ( fp, "%i", &imageArray[row][col]) ;
            }
        }
        fclose ( fp ) ;
    }

    return ;
}

int main( void )
{
    int height  = 0 ;
    int width = 0 ;
    int maxPixel = 0 ;

    //char* pgmInFileName = "lynx_central.pgm" ;
    //char* pgmOutFileName = "lynx_central_out.pgm" ;
    char* pgmInFileName = "irv.pgm" ;
    char* pgmOutFileName = "irv_out.pgm" ;

    // Read input file into array, then write it back out,
    // just to prove this all works.  Input file and output
    // file should look just the same.  (sizes on disk might
    // vary slightly)
    read_pgm_file_into_array (theImageArray, &height, &width, &maxPixel, pgmInFileName ) ;

    //****
    //**** Your code to transform the image goes here ...
    for(int i = 0; i < 1025; i++){
        for(int j = 0; j < MAX_WIDTH; j++){
            theImageArrayDup[i][j] = theImageArray[i][j];
        }
    }
    imageProcessing(theImageArray, theImageArrayDup,height,width);

    //Transfer the current values in theImageArray back to disk
    write_pgm_file_from_array ( pgmOutFileName, theImageArray, "# JR test file", height, width,
                                maxPixel ) ;

    printf ( "Copying %s to %s, height=%u, width=%u, maxPixel=%d\n", pgmInFileName,
             pgmOutFileName,
             height, width, maxPixel ) ;

    //system("pause");
    return 0 ;
}
