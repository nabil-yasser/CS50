#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE (512 * sizeof(uint8_t))

int main(int32_t argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./recover filename.raw\n");
        return 1;
    }

    // Open Memory Card raw File
    FILE *MemoryCard = fopen(argv[1], "r");
    if (MemoryCard == NULL)
    {
        printf("Couldn't open file\n");
        return 1;
    }
    uint8_t *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL)
    {
        return 1;
    }
    FILE *NewJpegFile = NULL;
    char *NewJpegName = malloc(8 * sizeof(uint8_t));
    uint32_t FileCounter = 0;

    // Until the end of file do this
    while (fread(buffer, BUFFER_SIZE, 1, MemoryCard))
    {
        // If start of JPEG file
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            if (FileCounter > 0)
            {
                fclose(NewJpegFile);
            }
            sprintf(NewJpegName, "%03i.jpg", FileCounter);
            NewJpegFile = fopen(NewJpegName, "w");
            FileCounter++;
        }
        if (FileCounter > 0)
        {
            fwrite(buffer, BUFFER_SIZE, 1, NewJpegFile);
        }
    }
    free(buffer);
    free(NewJpegName);
    fclose(MemoryCard);
    fclose(NewJpegFile);
}