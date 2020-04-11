/*
 * Aaron Kim
 * GMU Short Message Service System
 * Date: April 7, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GMUsms.h"

#define TRUE 1
#define FALSE 0
#define MAX 160
#define MIN 120

/* prints the menu and options for user to choose */
void Menu(char *input)
{
  char buffer[100];

  printf("[P]ack and save a line of text (options are 'P' or 'p')\n");
  printf("[U]npack and print a line of text (options are 'U' or 'u')\n");
  printf("[Q]uit (options are 'Q' or 'q')\n");
  printf("Enter a choice: ");
  fgets(buffer, 100, stdin);
  sscanf(buffer, "%c", input);
}

/* function that takes bytes from originalArray and packs them into packedArray */
void Pack(unsigned char *packedArray, size_t PASize, unsigned char *originalArray, size_t OASize)
{
  int a = 0;
  int b = 0;

/* loop until the end of the array is reached */
  while (a < PASize)
  {
    if (b < OASize)
    {
      packedArray[a] = originalArray[b] | (originalArray[b+1] << 6); /* A | B << 6 */
      packedArray[a+1] = (originalArray[b+1] >> 2) | (originalArray[b+2] << 4); /*B >> 2 | C << 4 */
      packedArray[a+2] = (originalArray[b+2] >> 4) | (originalArray[b+3] << 2); /* C >> 4 | D << 2 */
      a += 3;
      b += 4;
    }
    else
    {
      break;
    }
  }
}

/* function that takes the packed bits from packedArray and stores every byte into unpackedArray */
void Unpack(unsigned char *unpackedArray, size_t UASize, unsigned char *packedArray, size_t PASize)
{
  int a = 0;
  int b = 0;

  while (a < UASize)
  {
    if (b < PASize)
    {
      /* 1 << 2, 1 >> 2 */
      unpackedArray[a] = packedArray[b] << 2; /* Split shifts into 2 statements */
      unpackedArray[a] = unpackedArray[a] >> 2;

      /* 1 >> 6 | (2 << 4, 2 >> 2) */
      unpackedArray[a+1] = packedArray[b+1] << 4; /* split shifts into 2 statements */
      unpackedArray[a+1] = unpackedArray[a+1] >> 2;   
      unpackedArray[a+1] = (packedArray[b] >> 6) | unpackedArray[a+1];

      /* 2 >> 4 | (3 << 6, 3 >> 2) */
      unpackedArray[a+2] = packedArray[b+2] << 6; /* split shifts into 2 statements */
      unpackedArray[a+2] = unpackedArray[a+2] >> 2;   
      unpackedArray[a+2] = (packedArray[b+1] >> 4) | unpackedArray[a+2];
  
      /* 3 >> 2 */
      unpackedArray[a+3] = packedArray[b+2] >> 2;
      a += 4;
      b += 3;
    }
    else
    {
      break;
    }
  }
}

/* function that copies elements from one array/ buffer to another */
void Copy(char *array, char *array2)
{
  int i = 0;

  for (i = 0; i < MAX; i++)
  {
    array[i] = array2[i];
  }
}

/* function to clear an array (set all elements to null) */
void Clear(char *array, size_t arrSize)
{
  int i = 0;

  for (i = 0; i < arrSize; i++)
  {
    array[i] = 0;
  }
}

int main(int argc, char *argv[])
{
  unsigned char packedArray[MIN];
  unsigned char unpackedArray[MAX];
  int t = TRUE;
  char ch;
  char buffer[MAX];
  char file[MAX];
  FILE *infile;
  FILE *outfile;
  int i;
  char clearBuffer[MAX];
  
  while (t)
  {
    Menu(&ch);
    switch(ch)
    {
      case 'P':
      case 'p':
        printf("Please enter a filename: "); /* prompt user for output file name */ 
        fgets(buffer, MAX, stdin); /* read input and store into the buffer */
        sscanf(buffer, "%s", file); /* take string form buffer and store into file */
        Clear(clearBuffer, sizeof(clearBuffer)); /* clear the buffer */
        printf("Please enter a line of text: ");
        fgets(clearBuffer, MAX, stdin);
        Copy(buffer, clearBuffer); /* copy first 159 characters from clearBuffer to buffer */
        buffer[strlen(buffer) - 1] = 0; /* set newline character in buffer to null */
         
        /* clear input stream */
        while (clearBuffer[strlen(clearBuffer) - 1] != '\n')
        {
          fgets(clearBuffer, MAX, stdin);
        }
 
        /* open file in writing mode and append .sms to filename */
        outfile = fopen(strcat(file, ".sms"), "w");

        /* check to see if file was opened correctly */
        if (outfile == NULL)
        {
          printf("Error opening file\n");
          break;
        }
        
        /* Ascii to GMUSCII */
        for (i = 0; i < MAX; i++)
        {
          unpackedArray[i] = CharToSMS((unsigned char) buffer[i]);
        }   
    
        Pack(packedArray, sizeof(packedArray), unpackedArray, sizeof(unpackedArray)); /* pack the message */
        fwrite(packedArray, sizeof(unsigned char), MIN, outfile); /* write to output file */
        fclose(outfile);
        break;
      
      case 'U':
      case 'u':
        printf("Please enter a filename: ");
        fgets(buffer, MAX, stdin);
        sscanf(buffer, "%s", file);
        infile = fopen(strcat(file, ".sms"), "r");
 
        if (infile == NULL)
        {
          printf("Error opening file\n");
          break;
        }

        Clear(buffer, sizeof(buffer)); 
        fread(packedArray, sizeof(unsigned char), MIN, infile);
        Unpack(unpackedArray, sizeof(unpackedArray), packedArray, sizeof(packedArray)); /* unpack the message */
          
        /* GMUSCII to Ascii */
        for (i = 0; i < MAX; i++)
        {
          buffer[i] = SMSToChar(unpackedArray[i]);
        }

        printf("%s", buffer); /* print the unpacked message */
        printf("\n");
        fclose(infile);
        break;

      case 'Q':
      case 'q':
        t = FALSE;
        break;

      default:
        printf("Error, try again!\n");
    }

  }
  return 0; 
}







