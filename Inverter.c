#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "measureTime.h"
#include "stb_image.h"
#include "stb_image_write.h"

typedef struct{
    int startIndex;
    int endIndex;
    unsigned char* data;
    pthread_mutex_t* mux;
}pixelModifier;

int main(int argc, char** argv)
{
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    unsigned char* data;
    int width, height, depth = 3;
    char inputFilename[] = "testImage.jpg";
    char outputFilename[] = "invert.jpg";
    
    if(atoi(argv[1]) == 0)
    {
         // load data from file
        printf("Reading %s...\n",argv[1]);
        data = stbi_load(argv[1], &width, &height, NULL, depth);
    }
    else
    {
        // load data from file
        printf("Reading %s...\n",inputFilename);
        data = stbi_load(inputFilename, &width, &height, NULL, depth);
    }
    
    printf("Size of the image is %dx%d\n", width, height);

    if(atoi(argv[1]) != 0){
        printf("%d my number of threads \n",atoi(argv[1]));
        //Thread needs parameter
        // startIndex endIndex mutex data

    }
    else{
        // invert values
        unsigned long _begin = getTimestamp();
        printf("Started at %lu \n",_begin);
        int nbPixels = width * height * depth;
        for(unsigned int i = 0; i < nbPixels; i++)
        {
            data[i] = 255 - data[i];
        }
        unsigned long _end = getTimestamp();
        printf("Elapsed time... %lu us\n", _end - _begin);
    }

    printf("Writing %s...\n", outputFilename);
    // save data file
    stbi_write_png(outputFilename, width, height, depth, data, 0);
   
    free(data);
    
    return 0;
}




