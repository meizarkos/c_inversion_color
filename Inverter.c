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
}threadData;

void* invertPixel(void* arg){
    threadData* ctx = (threadData*)arg;
    for(int i=ctx->startIndex;i<ctx->endIndex;i++){
        ctx->data[i] = 255 - ctx->data[i];
    }
    return NULL;
}

int main(int argc, char** argv)
{
    unsigned char* data;
    int width, height, depth = 3;
    char inputFilename[] = "testImage.jpg";
    char outputFilename[] = "invert.jpg";

    if(argc == 2 && atoi(argv[1])==0)
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

    int numberOfThread = atoi(argv[1]);
    if(numberOfThread == 0){
        numberOfThread = 1;
    }
    printf("%d my number of threads \n\n",numberOfThread);
    unsigned long _begin = getTimestamp();
    printf("Start %lu \n",_begin);
    threadData threadData[numberOfThread];
    pthread_t threads[numberOfThread];
    int nbPixels = width * height * depth;
    int pixelPerThread = nbPixels / numberOfThread;
    for(int i = 0; i < numberOfThread ; i++){
        threadData[i].startIndex = i * pixelPerThread;
        threadData[i].endIndex = (i == numberOfThread - 1) ? nbPixels : (i + 1) * pixelPerThread;
        threadData[i].data = data;
        pthread_create(&threads[i], NULL, invertPixel, &threadData[i]);
    }

    for(int i = 0; i < numberOfThread; i++){
        pthread_join(threads[i], NULL);
    }
    unsigned long _end = getTimestamp();
    printf("Elapsed time... %lu us\n", _end - _begin);

    printf("Writing %s...\n", outputFilename);
    // save data file
    stbi_write_png(outputFilename, width, height, depth, data, 0);
   
    free(data);
    
    return 0;
}




