#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* This struct initializes the Music structure and allows us to modify its values
*
* routine: Music
*
* return type: void
*
* parameters:
*	No parameters
*
* @author	Abdel Rahman Mansour
* @since	02/18/2021
*/
struct Music
{
	char artist[100];
	char genre[100];
}Music;

/*
* This struct initializes the Book structure and allows us to modify its values
*
* routine: Book
*
* return type: void
*
* parameters:
*	No parameters
*
* @author	Abdel Rahman Mansour
* @since	02/18/2021
*/
struct Book
{
	char author[100];
	char genre[100];
}Book;

/*
* This struct initializes the Movie structure and allows us to modify its values
*
* routine: Movie
*
* return type: void
*
* parameters:
*	No parameters
*
* @author	Abdel Rahman Mansour
* @since	02/18/2021
*/
struct Movie
{
	char rating[100];
}Movie;

/*
* This struct initializes all the media structures in a union, allows us to modify their values, 
* and contains some values that are common to all the Media structures
*
* routine: MediaStruct
*
* return type: void
*
* parameters:
*	No parameters
*
* @author	Abdel Rahman Mansour
* @since	02/18/2021
*/
struct MediaStruct
{
	char name[100];
	char releaseYear[5];
	char genreType[10];

	union AllMedia
	{
		struct Music music;
		struct Book book;
		struct Movie movie;
	}Media;
}MediaStruct;

/*
* This method swaps the values of two structs that are passed are a parameter
*
* routine: Swap
*
* return type: void
*
* parameters:
*	struct1	[MediaStruct*]		The first structure to be swapped with the second.
*
*	struct2	[MediaStruct*]		The second structure to be swapped with the first.
*
* @author	Abdel Rahman Mansour
* @since	02/20/2021
*/
void Swap(struct MediaStruct* struct1, struct MediaStruct* struct2)
{
	struct MediaStruct temp = *struct1;
	*struct1 = *struct2;
	*struct2 = temp;
}

/*
* This method sorts the struct array using the normal bubble sort algorithm based on their names
*
* routine: BubbleSort
*
* return type: void
*
* parameters:
*	structArray[]	[MediaStruct*]		The array of structs to be sorted passed on the name.
*
*	arraySize		[int]				Size of the array of structs to be sorted.
*
* @author	Abdel Rahman Mansour
* @since	02/20/2021
*/
void BubbleSort(struct MediaStruct* structArray[] , int arraySize)
{
	for (int i = 0; i < arraySize - 1; i++)
	{
		for (int j = 0; j < arraySize - i - 1; j++)
		{
			if (strcmp(structArray[j]->name , structArray[j + 1]->name) > 0)
			{
				Swap(structArray[j] , structArray[j + 1]);
			}
		}
	}
}

/**
* This program inputs a set of digital media library values from a
* text file, stores those values in an array of struct pointers, sorts the array, and prints the final
* contents of the array to a separate text file
*
* CSC 3304 Programming project No. 2
*
* @author	Abdel Rahman Mansour
* @since	02/18/2021
*
*/
int main()
{
	FILE* input = fopen("./TestInput.txt", "r");
	FILE* output = fopen("./out.txt", "w");

	int numRows = 500;
	int numColumns = 100;
	int EOFcheck = 0;
	int i = 0;
	int j = 0;
	int arraySize = 0;

	int structArrayPointer = 0;
	struct MediaStruct* (structArray[100]);

	char** stringArray = (char**)malloc(numRows * sizeof(char*));

	for (int i = 0; i < 100; i++) 
	{
		structArray[i] = (struct MediaStruct*)malloc(sizeof(MediaStruct));
	}

	if (stringArray == NULL)
	{
		printf("Couldn't allocate memory");
	}
	else
	{
		for (i = 0; i < numRows; i++)
		{
			stringArray[i] = malloc(numColumns * sizeof(char));
		}
	}

	while ((EOFcheck = getc(input)) != EOF && j < 500)
	{
		ungetc(EOFcheck, input);
		fgets(stringArray[j], 100, input);
		arraySize = arraySize + 1;
		j = j + 1;
	}

	for (i = 0; i < arraySize; i++)
	{
		if (strcmp(stringArray[i], "music\n") == 0)
		{
			strncpy(structArray[structArrayPointer]->genreType, stringArray[i], 100);
			strncpy(structArray[structArrayPointer]->name, stringArray[i + 1], 100);
			strncpy(structArray[structArrayPointer]->Media.music.artist , stringArray[i + 2], 100);
			strncpy(structArray[structArrayPointer]->Media.music.genre , stringArray[i + 3], 100);
			strncpy(structArray[structArrayPointer]->releaseYear , stringArray[i + 4], 5);

			structArray[structArrayPointer]->releaseYear[4] = '\0';

			structArrayPointer = structArrayPointer + 1;
			i = i + 4;
		}

		else if (strcmp(stringArray[i], "book\n") == 0)
		{
			strncpy(structArray[structArrayPointer]->genreType, stringArray[i], 100);
			strncpy(structArray[structArrayPointer]->name, stringArray[i + 1], 100);
			strncpy(structArray[structArrayPointer]->Media.book.author, stringArray[i + 2], 100);
			strncpy(structArray[structArrayPointer]->Media.book.genre, stringArray[i + 3], 100);
			strncpy(structArray[structArrayPointer]->releaseYear, stringArray[i + 4], 5);

			structArray[structArrayPointer]->releaseYear[4] = '\0';

			structArrayPointer = structArrayPointer + 1;
			i = i + 4;
		}

		else if (strcmp(stringArray[i], "movie\n") == 0)
		{
			strncpy(structArray[structArrayPointer]->genreType, stringArray[i], 100);
			strncpy(structArray[structArrayPointer]->name, stringArray[i + 1], 100);
			strncpy(structArray[structArrayPointer]->Media.movie.rating, stringArray[i + 2], 100);
			strncpy(structArray[structArrayPointer]->releaseYear, stringArray[i + 3], 5);

			structArray[structArrayPointer]->releaseYear[4] = '\0';

			structArrayPointer = structArrayPointer + 1;
			i = i + 3;
		}
	}

	BubbleSort(structArray , structArrayPointer);

	for (i = 0; i < structArrayPointer; i++)
	{
		if (strcmp(structArray[i]->genreType, "music\n") == 0)
		{
			fputs(structArray[i]->genreType, output);
			fputs(structArray[i]->name, output);
			fputs(structArray[i]->Media.music.artist, output);
			fputs(structArray[i]->Media.music.genre, output);
			fputs(structArray[i]->releaseYear, output);

			fputs("\n\n", output);
		}

		else if (strcmp(structArray[i]->genreType, "book\n") == 0)
		{
			fputs(structArray[i]->genreType, output);
			fputs(structArray[i]->name, output);
			fputs(structArray[i]->Media.book.author, output);
			fputs(structArray[i]->Media.book.genre, output);
			fputs(structArray[i]->releaseYear, output);

			fputs("\n\n", output);
		}

		else if (strcmp(structArray[i]->genreType, "movie\n") == 0)
		{
			fputs(structArray[i]->genreType , output);
			fputs(structArray[i]->name, output);
			fputs(structArray[i]->Media.movie.rating, output);
			fputs(structArray[i]->releaseYear, output);

			fputs("\n\n", output);
		}
	}

	fclose(input);
	fclose(output);

	for (int i = 0; i < arraySize; i++)
	{
		free(stringArray[i]);
	}
	free(stringArray);

	for (int i = 0; i < 100 ; i++) 
	{
		free(structArray[i]);
	}

	return 0;
}