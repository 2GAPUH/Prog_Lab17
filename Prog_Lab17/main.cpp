#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define FixedRows 20
#define	FixedColumns 30


struct ArraySize
{
	int Rows, Columns;
};

typedef double MyArray[FixedRows][FixedColumns];


void ArrayPrinting(ArraySize UserArraySize, double Array[FixedRows][FixedColumns])
{
	for (int i = 0;i != UserArraySize.Rows; i++)
	{
		for (int n = 0; n != UserArraySize.Columns; n++)
		{
			printf_s("Array[%d][%d] = %lf\t", i, n, Array[i][n]);
		}
		printf_s("\n");
	}
}


int ArraySizeChecking(ArraySize UserArraySize)
{
	bool check;

	if (UserArraySize.Rows > FixedRows || UserArraySize.Columns > FixedColumns)
	{
		printf_s("The custom array is larger than the fixed array, data loss is possible.End the program? \n0 - Yes \n1 - No \n");
		do {
			scanf_s("%d", &check);
			switch (check)
			{
			case 0:exit(1);break;
			case 1:break;

			default: printf_s("Invalid Value! Try again.\n");
			}
		} while (check < 0 || check > 1);
	}

	return 0;
}


int ManualArrayFilling(ArraySize UserArraySize, double Array[FixedRows][FixedColumns])
{
	for (int i = 0; i != UserArraySize.Rows; i++)
	{
		for (int n = 0; n != UserArraySize.Columns; n++)
		{
			printf_s("Enter [%d][%d] ellement of Array: ", i, n);
			scanf_s("%lf", &Array[i][n]);
		}
	}
	return 0;
}

ArraySize TextFileArrayFilling(double Array[FixedRows][FixedColumns])
{
	FILE* userFileInput;
	char fileName[25];
	ArraySize UserArraySize;

	printf("Enter the name of the processed file(file.txt): ");
	while (getchar() != '\n');
	gets_s(fileName);

	if (fopen_s(&userFileInput, fileName, "r") != 0)
	{
		printf_s("Error opening file!\n");
		exit(1);
	}

	fscanf_s(userFileInput, "%d", &UserArraySize.Rows);
	fscanf_s(userFileInput, "%d", &UserArraySize.Columns);

	ArraySizeChecking(UserArraySize);

	for (int i = 0; i != UserArraySize.Rows; i++)
	{
		for (int n = 0; n != UserArraySize.Columns; n++)
		{
			fscanf_s(userFileInput, "%lf", &Array[i][n]);
		}
	}

	printf_s("Successful Copy!\n");

	fclose(userFileInput);

	return UserArraySize;
}


ArraySize BinFileArrayFilling(double Array[FixedRows][FixedColumns])
{
	FILE* UserFileInput;
	char FileName[30];
	ArraySize UserArraySize;
	bool check;

	printf_s("Enter the name of the processed file(file.bin): ");
	while (getchar() != '\n');
	gets_s(FileName);

	if (fopen_s(&UserFileInput, FileName, "rb") != 0)
	{
		printf_s("Error opening file!\n");
		exit(1);
	}

	fread(&UserArraySize.Rows, sizeof(int), 1, UserFileInput);
	fread(&UserArraySize.Columns, sizeof(int), 1, UserFileInput);

	ArraySizeChecking(UserArraySize);

	for (int i = 0; i < UserArraySize.Rows; i++)
		fread(&Array[i], sizeof(double), UserArraySize.Columns, UserFileInput);

	printf_s("Successful Copy!\n");

	fclose(UserFileInput);

	return UserArraySize;
}


int RandomArrayFilling(ArraySize UserArraySize, double Array[FixedRows][FixedColumns])
{
	int seed = time(NULL);
	srand(seed);

	for (int i = 0; i != UserArraySize.Rows; i++)
	{
		for (int n = 0; n != UserArraySize.Columns; n++)
		{
			Array[i][n] = rand();
		}
	}

	printf_s("Successful Generation!\n");

	return seed;
}


void FormulaArrayFilling(ArraySize UserArraySize, double Array[FixedRows][FixedColumns])
{
	for (int i = 0; i != UserArraySize.Rows; i++)
	{
		for (int n = 0; n != UserArraySize.Columns; n++)
		{
			if ((i+1) < (n+1)) Array[i][n] = 1.0 / ((i+1) + (n+1) - 1);
			else if ((i+1) == (n+1)) Array[i][n] = 0;
			else Array[i][n] = -1.0 / ((i+1) + (n+1) - 1);
		}
	}

	printf_s("Successful Generation!\n");
}


int TextFileArraySave(ArraySize UserArraySize, double Array[FixedRows][FixedColumns])
{
	FILE* UserFileOutput;
	char FileName[40];

	printf_s("Enter name of file(global path or name): ");
	while (getchar() != '\n');
	gets_s(FileName);

	if (fopen_s(&UserFileOutput, FileName, "a") != 0)
	{
		printf_s("Error opening file!\n");
		return -1;
	}

	fprintf_s(UserFileOutput, "%d %d\n", UserArraySize.Rows, UserArraySize.Columns);

	for (int i = 0; i < UserArraySize.Rows; i++)
	{
		for (int n = 0; n < UserArraySize.Columns; n++)
			fprintf_s(UserFileOutput, "%lf ", Array[i][n]);
		fprintf_s(UserFileOutput, "\n");
	}
	return 0;
}


int BinFileArraySave(ArraySize UserArraySize, double Array[FixedRows][FixedColumns])
{
	FILE* UserFileOutput;
	char FileName[40];

	printf_s("Enter name of file(global path or name): ");
	while (getchar() != '\n');
	gets_s(FileName);

	if (fopen_s(&UserFileOutput, FileName, "ab") != 0)
	{
		printf_s("Error opening file!\n");
		return -1;
	}

	fwrite(&UserArraySize.Rows, sizeof(int), 1, UserFileOutput);
	fwrite(&UserArraySize.Columns, sizeof(int), 1, UserFileOutput);

	for (int i = 0;i < UserArraySize.Rows;i++)
		fwrite(Array[i], sizeof(double), UserArraySize.Columns, UserFileOutput);


	return 0;
}


ArraySize GetArraySize(int Rows, int Colomns)
{
	ArraySize UserArraySize;
	do {
		printf_s("Enter array size(1 < n < %d): ", Rows);
		scanf_s("%d", &UserArraySize.Rows);
		if (UserArraySize.Rows > Rows || UserArraySize.Rows < 2) printf_s("Incorrect value!Try again.\n");
	} while (UserArraySize.Rows > Rows || UserArraySize.Rows < 2);

	do {
		printf_s("Enter array size(1 < n < %d): ", Colomns);
		scanf_s("%d", &UserArraySize.Columns);
		if (UserArraySize.Columns > Colomns || UserArraySize.Columns < 2) printf_s("Incorrect value!Try again.\n");
	} while (UserArraySize.Columns > Colomns || UserArraySize.Columns < 2);

	return UserArraySize;
}



int main()
{
	system("chcp 1251");

	int TypeOfFilling, TypeOfSaving;
	ArraySize UserArraySize;
	int seed;

	double Array[FixedRows][FixedColumns];

	printf_s("0 - Exit \n1 - Manual Array Filling \n2 - Text File Array Filling \n3 - Bin File Array Filling \n4 - Random Array Filling \n5 - Formula Array Filling \n");
	do {
		printf_s("Enter type of Filling : ");
		scanf_s("%d", &TypeOfFilling);
		switch (TypeOfFilling)
		{
		case 0: return 0; break;
		case 1: UserArraySize = GetArraySize(FixedRows, FixedColumns); ManualArrayFilling(UserArraySize, Array); break;
		case 2: UserArraySize = TextFileArrayFilling(Array); break;
		case 3: UserArraySize = BinFileArrayFilling(Array); break;
		case 4: UserArraySize = GetArraySize(FixedRows, FixedColumns); seed = RandomArrayFilling(UserArraySize, Array); break;
		case 5: UserArraySize = GetArraySize(FixedRows, FixedColumns); FormulaArrayFilling(UserArraySize, Array); break;

		default: printf_s("Incorrect value!Try again.\n"); break;
		}
	} while (TypeOfFilling < 0 || TypeOfFilling > 5);

	printf_s("0 - Exit \n1 - Array printing \n2 - Text file array save \n3 - Bin file array save \n");
	do {
		printf_s("Enter type of saving: ");
		scanf_s("%d", &TypeOfSaving);
		switch (TypeOfSaving)
		{
		case 0: return 0;
		case 1: ArrayPrinting(UserArraySize, Array); break;
		case 2: TextFileArraySave(UserArraySize, Array); break;
		case 3: BinFileArraySave(UserArraySize, Array); break;

		default: printf_s("Incorrect value!Try again.\n"); break;
		}
	} while (TypeOfSaving != 0);

	return 0;
}