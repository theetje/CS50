int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");

        return 1;
    }

    // remember filenames
    char *cardraw = argv[1];


    // open input file
    FILE *cardptr = fopen("card.raw", "r");
    if (cardptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", cardraw);
        return 2;
    }

    // create newpicture and some variables
    FILE *newpicture = NULL;

    int buffersize = 512;

    unsigned char buffer[buffersize];

    int filenamecounter = 0;

    int isjpg = 0;

    // iterate through the file, in bricks of 512 bits
    while (fread(buffer, buffersize, 1, cardptr) == 1)
    {
        // search for a .jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (isjpg == 1)
            {
                fclose(newpicture);
            }
            else
            {
                isjpg = 1;
            }

            filenamecounter += 1;

            char filename[11];

            // create a new imagefile
            sprintf(filename, "%03i.jpg", filenamecounter);

            // open the new imagefile
            newpicture = fopen(filename, "w");
        }

        // write in the new image file
        if (isjpg == 1)
        {

            fwrite(&buffer, buffersize, 1, newpicture);
        }
    }


    return 0;


}