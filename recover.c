#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BUFFER_SIZE (512 * sizeof(uint8_t))

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./recover Filename.raw\n");
        return 1;
    }
    // Open memory Card
    FILE* MemoryCard = fopen(argv[1], "r");
    if (MemoryCard == NULL)
    {
        printf("File Can't be opened\n");
        return 1;
    }
    uint8_t* buffer = malloc(BUFFER_SIZE);
    uint32_t FileCounter = 0;
    if (buffer == NULL)
    {
        return 1;
    }
    // Repeat until the end of Card
    // Read 512 bytes into a buffer
    char* NewName = NULL;
    FILE* NewJpeg = NULL;
    while (fread(buffer, BUFFER_SIZE, 1, MemoryCard) == BUFFER_SIZE)
    {
        // If start of new JPEG
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            sprintf(NewName, "%03i", FileCounter);
            if (FileCounter > 0)
            {
                fclose(NewJpeg);
            }
            NewJpeg = fopen(NewName, "w");
            FileCounter++;
        }
        fwrite(buffer, BUFFER_SIZE, 1, NewJpeg);
    }
    // Close Any remaining files
    fclose(MemoryCard);
    free(buffer);
    return 0;
}