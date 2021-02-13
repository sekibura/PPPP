#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void initMatrix(int**& matrix, string message, int* ColsNumber, int* RowsNumber);
bool isSizeCorrect(int a, int b);
void fillMatrixRandom(int** matrix, int* ColsNumber, int* RowsNumber);
void fillMatrixByUser(int** matrix, int* ColsNumber, int* RowsNumber);
void chooseFillingMattrix(int** matrixA, int* colsNumberA, int* rowsNumberA, int** matrixB, int* colsNumberB, int* rowsNumberB);
void printMatrix(int** matrix, int ColsNumber, int RowsNumber, string message);
void matrixToTargetSize(int** matrixS, int ColsNumber, int RowsNumber, int targetSize, int**& matrixD);
void matrixExpandZeros(int**& matrix, int size);
void uniteMatrix(int** matrixSource, int ColsNumberS, int RowsNumberS, int** matrixDestination);
int*** calcIntermediateMatrixs(int** sourceMatrixA, int** sourceMatrixB, int size);
int*** cutMatrix(int** sourceMatrixA, int** sourceMatrixB, int size);
int*** tmpMatrix(int size);
void calcValueIntrmdMatr(int*** tmpMatr, int*** cutedMtx, int size);
int*** helpMatrix(int*** intermdMatrix, int size);
int*** createHelpMtx(int size);
void calcHelpMatrix(int*** helpMatrix, int*** intermMatrix, int size);
int** createResultMatrix(int size);
void fromHelpToResultMatrix(int** resMatrix, int*** helpMatrix, int size);
int** bordersResMatrix(int** resMatrix, int size, int* R_SizeMatrixColumns, int* R_SizeMatrixRows);
int** result(int*** helpMatrix, int size, int* R_SizeMatrixColumns, int* R_SizeMatrixRows);
void clearMemoryMatrix(int** matrix, int cols);

int main() 
{
	srand(time(NULL));
	system("chcp 1251");
	int A_SizeMatrixRows = 0;
	int A_SizeMatrixColumns = 0;
	int R_SizeMatrixRows = 0;
	int R_SizeMatrixColumns = 0;
	int B_SizeMatrixRows = 0;
	int B_SizeMatrixColumns = 0;
	int** A_Matrix = nullptr;
	int** B_Matrix= nullptr;
	int expandedMatrixSize = 2;
	int** A_ExpandedMatrix = nullptr;
	int** B_ExpandedMatrix = nullptr;
	int*** intermdMatrix = nullptr;
	int*** helpMtx = nullptr;
	int** resultMatrix = nullptr;
	cout << "Вас приветствует программа\nбыстрого перемножения матриц методом Штрассена\n\n";

	initMatrix(A_Matrix,"Введите размеры первой матрицы\n",&A_SizeMatrixColumns,&A_SizeMatrixRows);
	initMatrix(B_Matrix, "Введите размеры второй матрицы\n", &B_SizeMatrixColumns, &B_SizeMatrixRows);

	chooseFillingMattrix(A_Matrix, &A_SizeMatrixColumns, &A_SizeMatrixRows, B_Matrix,&B_SizeMatrixColumns, &B_SizeMatrixRows);
	
	printMatrix(A_Matrix, A_SizeMatrixColumns, A_SizeMatrixRows,"Первая матрица");
	printMatrix(B_Matrix, B_SizeMatrixColumns, B_SizeMatrixRows, "Вторая матрица");

	while (expandedMatrixSize < A_SizeMatrixColumns || expandedMatrixSize < A_SizeMatrixRows || expandedMatrixSize < B_SizeMatrixColumns || expandedMatrixSize < B_SizeMatrixRows)
		expandedMatrixSize *= 2;

	matrixToTargetSize(A_Matrix, A_SizeMatrixColumns, A_SizeMatrixRows, expandedMatrixSize, A_ExpandedMatrix);
	matrixToTargetSize(B_Matrix, B_SizeMatrixColumns, B_SizeMatrixRows, expandedMatrixSize, B_ExpandedMatrix);

	printMatrix(A_ExpandedMatrix, expandedMatrixSize, expandedMatrixSize,"Первая приведенная матрица");
	printMatrix(B_ExpandedMatrix, expandedMatrixSize, expandedMatrixSize, "Вторая приведенная матрица");

	intermdMatrix = calcIntermediateMatrixs(A_ExpandedMatrix, B_ExpandedMatrix, expandedMatrixSize);
	helpMtx = helpMatrix(intermdMatrix, expandedMatrixSize);
	resultMatrix = result(helpMtx, expandedMatrixSize,&R_SizeMatrixColumns,&R_SizeMatrixRows);
	printMatrix(resultMatrix, R_SizeMatrixColumns, R_SizeMatrixRows, "\nРезультирующая матрица");

	clearMemoryMatrix(A_Matrix, A_SizeMatrixColumns);
	clearMemoryMatrix(B_Matrix, B_SizeMatrixColumns);
	clearMemoryMatrix(A_ExpandedMatrix, expandedMatrixSize);
	clearMemoryMatrix(B_ExpandedMatrix, expandedMatrixSize);
	clearMemoryMatrix(resultMatrix, R_SizeMatrixColumns);
	for (int i = 0; i < 7; i++)
	{
		clearMemoryMatrix(intermdMatrix[i],expandedMatrixSize/2);
	}
	for (int i = 0; i < 4; i++)
	{
		clearMemoryMatrix(helpMtx[i], expandedMatrixSize / 2);
	}
	system("Pause");
	return 0;
}

void initMatrix(int**&matrix,string message, int* ColsNumber,int* RowsNumber) {
	
	while (!isSizeCorrect(*ColsNumber,*RowsNumber)) {
		cout << message << endl;
		cin >> *ColsNumber >> *RowsNumber;
	}

	int** newMatrix = new int* [*RowsNumber];
	for (int i = 0; i < *RowsNumber; i++)
		newMatrix[i] = new int[*ColsNumber];
	matrix = newMatrix;
}
bool isSizeCorrect(int a,int b) {
	return a > 0 && b > 0;
}
void chooseFillingMattrix(int** matrixA, int* colsNumberA, int* rowsNumberA, int** matrixB, int* colsNumberB, int* rowsNumberB) {
	int input = 0;
	
	while (input!=1 && input!=2) {
		cout << "Введите цифру 1 или 2:\n"<<
				"1 - заполнить матрицы вручную\n"<<
				"2- заполнить матрицы случайным образом" << endl;
		cin >> input;
	}
	if (input == 1) {
		fillMatrixByUser(matrixA,colsNumberA,rowsNumberA);
		fillMatrixByUser(matrixB, colsNumberB, rowsNumberB);
	}
	else {
		fillMatrixRandom(matrixA, colsNumberA, rowsNumberA);
		fillMatrixRandom(matrixB, colsNumberB, rowsNumberB);
	}

}
void fillMatrixRandom(int** matrix, int* ColsNumber, int* RowsNumber) {
	for (int i = 0; i < *ColsNumber; i++)
		for (int j = 0; j < *RowsNumber; j++)
			matrix[i][j] = rand() % 10;
}
void fillMatrixByUser(int** matrix, int* ColsNumber, int* RowsNumber) {
	for (int i = 0; i < *ColsNumber; i++)
		for (int j = 0; j < *RowsNumber; j++)
		{
			cout << "\nВведите значение элемента " << i << " " << j<< endl;
			cin >> matrix[i][j];
		}			
}
void printMatrix(int** matrix, int ColsNumber, int RowsNumber,string message) {
	cout << message << endl;
	for (int i = 0; i < ColsNumber; i++)
	{
		for (int j = 0; j < RowsNumber; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}
void matrixToTargetSize(int** matrixS, int ColsNumber, int RowsNumber,int targetSize,int**&matrixD)
{

	matrixExpandZeros(matrixD,targetSize);
	uniteMatrix(matrixS, ColsNumber, RowsNumber, matrixD);
}
void matrixExpandZeros(int**&matrix,int size) 
{
	int** newMatrix = new int* [size];
	for (int i = 0; i < size; i++)
	{
		newMatrix[i] = new int[size];
		for (int j = 0; j < size; j++)
			newMatrix[i][j] = 0;
	}
	matrix = newMatrix;
}
void uniteMatrix(int** matrixSource, int ColsNumberS, int RowsNumberS, int** matrixDestination) {
	for (int i = 0; i < ColsNumberS; i++)
	{
		for (int j = 0; j < RowsNumberS; j++)
			matrixDestination[i][j] = matrixSource[i][j];
	}
}
int*** calcIntermediateMatrixs(int** sourceMatrixA, int** sourceMatrixB,int size) 
{
	int *** cutedMatrix=cutMatrix(sourceMatrixA, sourceMatrixB, size);
	int*** tmpMtx = tmpMatrix(size);
	calcValueIntrmdMatr(tmpMtx, cutedMatrix, size);
	for (int i = 0; i < 8; i++)
	{
		clearMemoryMatrix(cutedMatrix[i], size / 2);
	}
	return tmpMtx;

}
int*** cutMatrix(int** sourceMatrixA, int** sourceMatrixB,int size) {
	int** mat1 = new int* [size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		mat1[i] = new int[size / 2];
		for (int j = 0; j < size / 2; j++)
			mat1[i][j] = sourceMatrixA[i][j];
	}
	int** mat2 = new int* [size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		mat2[i] = new int[size / 2];
		for (int j = 0; j < size / 2; j++)
			mat2[i][j] = sourceMatrixA[i][j + size / 2];
	}
	int** mat3 = new int* [size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		mat3[i] = new int[size / 2];
		for (int j = 0; j < size / 2; j++)
			mat3[i][j] = sourceMatrixA[i + size / 2][j];
	}
	int** mat4 = new int* [size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		mat4[i] = new int[size / 2];
		for (int j = 0; j < size / 2; j++)
			mat4[i][j] = sourceMatrixA[i + size / 2][j + size / 2];
	}
	int** mat5 = new int* [size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		mat5[i] = new int[size / 2];
		for (int j = 0; j < size / 2; j++)
			mat5[i][j] = sourceMatrixB[i][j];
	}
	int** mat6 = new int* [size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		mat6[i] = new int[size / 2];
		for (int j = 0; j < size / 2; j++)
			mat6[i][j] = sourceMatrixB[i][j + size / 2];
	}
	int** mat7 = new int* [size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		mat7[i] = new int[size / 2];
		for (int j = 0; j < size / 2; j++)
			mat7[i][j] = sourceMatrixB[i + size / 2][j];
	}
	int** mat8 = new int* [size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		mat8[i] = new int[size / 2];
		for (int j = 0; j < size / 2; j++)
			mat8[i][j] = sourceMatrixB[i + size / 2][j + size / 2];
	}
	int*** partsMatrix = new int** [8]{mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8};
	return partsMatrix;
}
int*** tmpMatrix(int size) {
	int*** arrayOfMatrixs = new int** [7];
	for (int i = 0; i < 7; i++)
	{
		int** newMtx = new int* [size / 2];
		for (int i = 0; i < size / 2; i++)
		{
			newMtx[i] = new int[size / 2];
		}
		arrayOfMatrixs[i] = newMtx;
	}
	return arrayOfMatrixs;
}
void calcValueIntrmdMatr(int*** tmpMatr,int***cutedMtx,int size) {
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			tmpMatr[0][i][j] = 0;
			for (int z = 0; z < size / 2; z++)
			{
				tmpMatr[0][i][j] += (cutedMtx[0][i][z] + cutedMtx[3][i][z]) * (cutedMtx[4][z][j] + cutedMtx[7][z][j]);
			}

			tmpMatr[1][i][j] = 0;
			for (int z = 0; z < size / 2; z++)
			{
				tmpMatr[1][i][j] += (cutedMtx[2][i][z] + cutedMtx[3][i][z]) * cutedMtx[4][z][j];
			}

			tmpMatr[2][i][j] = 0;
			for (int z = 0; z < size / 2; z++)
			{
				tmpMatr[2][i][j] += cutedMtx[0][i][z] * (cutedMtx[5][z][j] - cutedMtx[7][z][j]);
			}

			tmpMatr[3][i][j] = 0;
			for (int z = 0; z < size / 2; z++)
			{
				tmpMatr[3][i][j] += cutedMtx[3][i][z] * (cutedMtx[6][z][j] - cutedMtx[4][z][j]);
			}

			tmpMatr[4][i][j] = 0;
			for (int z = 0; z < size / 2; z++)
			{
				tmpMatr[4][i][j] += (cutedMtx[0][i][z] + cutedMtx[1][i][z]) * cutedMtx[7][z][j];
			}

			tmpMatr[5][i][j] = 0;
			for (int z = 0; z < size / 2; z++)
			{
				tmpMatr[5][i][j] += (cutedMtx[2][i][z] - cutedMtx[0][i][z]) * (cutedMtx[4][z][j] + cutedMtx[5][z][j]);
			}

			tmpMatr[6][i][j] = 0;
			for (int z = 0; z < size / 2; z++)
			{
				tmpMatr[6][i][j] += (cutedMtx[1][i][z] - cutedMtx[3][i][z]) * (cutedMtx[6][z][j] + cutedMtx[7][z][j]);
			}
		}
	}
}
int*** helpMatrix(int*** intermdMatrix,int size) {
	int*** hlpMtx=createHelpMtx(size);
	calcHelpMatrix(hlpMtx, intermdMatrix, size);
	return hlpMtx;
}
int*** createHelpMtx(int size) {
	int*** newMtx = new int** [4];
	for (int i = 0; i < 4; i++)
	{
		int** mat = new int* [size / 2];
		for (int i = 0; i < size / 2; i++)
		{
			mat[i] = new int[size / 2];
		}
		newMtx[i] = mat;
	}
	return newMtx;
}
void calcHelpMatrix(int*** helpMatrix,int*** intermMatrix,int size) {
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			helpMatrix[0][i][j] = intermMatrix[0][i][j] + intermMatrix[3][i][j] - intermMatrix[4][i][j] + intermMatrix[6][i][j];
			helpMatrix[1][i][j] = intermMatrix[2][i][j] + intermMatrix[4][i][j];
			helpMatrix[2][i][j] = intermMatrix[1][i][j] + intermMatrix[3][i][j];
			helpMatrix[3][i][j] = intermMatrix[0][i][j] - intermMatrix[1][i][j] + intermMatrix[2][i][j] + intermMatrix[5][i][j];
		}
	}
}
int** result(int*** helpMatrix,int size,int* R_SizeMatrixColumns,int* R_SizeMatrixRows) {
	int** resMatrix = createResultMatrix(size);
	fromHelpToResultMatrix(resMatrix, helpMatrix, size);
	int** result = bordersResMatrix(resMatrix, size,  R_SizeMatrixColumns,  R_SizeMatrixRows);
	clearMemoryMatrix(resMatrix, *R_SizeMatrixColumns);
	return result;
}
int** createResultMatrix(int size) {
	int** result = new int* [size];
	for (int i = 0; i < size; i++)
	{
		result[i] = new int[size];
	}
	return result;
}
void fromHelpToResultMatrix(int** resMatrix, int*** helpMatrix, int size) {
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			resMatrix[i][j] = helpMatrix[0][i][j];
			resMatrix[i][j + size / 2] = helpMatrix[1][i][j];
			resMatrix[i + size / 2][j] = helpMatrix[2][i][j];
			resMatrix[i + size / 2][j + size / 2] = helpMatrix[3][i][j];
		}
	}
}
int** bordersResMatrix(int** resMatrix,int size, int* R_SizeMatrixColumns, int* R_SizeMatrixRows) {
	int x = 0;
	*R_SizeMatrixColumns = 100;
	*R_SizeMatrixRows = 100;
	for (int i = 0; i < size; i++)
	{
		x = 0;
		for (int j = 0; j < size; j++)
		{
			if (resMatrix[i][j] != 0)
			{
				x++;
				*R_SizeMatrixColumns = 100;
			}
		}
		if (x == 0 && i < *R_SizeMatrixColumns)
		{
			*R_SizeMatrixColumns = i;
		}
	}
	for (int i = 0; i < size; i++)
	{
		x = 0;
		for (int j = 0; j < size; j++)
		{
			if (resMatrix[j][i] != 0)
			{
				x++;
				*R_SizeMatrixRows = 100;
			}
		}
		if (x == 0 && i < *R_SizeMatrixRows)
		{
			*R_SizeMatrixRows = i;
		}
	}
	int** M6 = new int* [*R_SizeMatrixColumns];
	for (int i = 0; i < *R_SizeMatrixColumns; i++)
	{
		M6[i] = new int[*R_SizeMatrixRows];
		for (int j = 0; j < *R_SizeMatrixRows; j++)
			M6[i][j] = resMatrix[i][j];
	}
	return M6;
}
void clearMemoryMatrix(int** matrix, int cols) {
	for (int i = 0; i < cols; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

}