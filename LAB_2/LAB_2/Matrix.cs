using System;
using System.Text;

namespace LAB_2
{
    class Matrix
    {
        private readonly int sizeRows;
        private readonly int sizeColumns;
        private readonly int[,] matrix;
        public Matrix(int n, int m)
        {
            sizeRows = (n >= 0) ? n : 0;
            sizeColumns = (m >= 0) ? m : 0;
            matrix = new int[sizeRows, sizeColumns];
            Console.OutputEncoding = Encoding.Unicode;
        }
        private bool NotOutOfTheRange(int row_index, int column_index)
        {
            return (row_index >= 0 && row_index < sizeRows) && (column_index >= 0 && column_index < sizeColumns);
        }
        public int this[int indexRow, int indexColumn]
        {
            set
            {
                matrix[indexRow, indexColumn] = (NotOutOfTheRange(indexRow, indexColumn)) ? value : 0;
            }
            get
            {
                return (NotOutOfTheRange(indexRow, indexColumn)) ? matrix[indexRow, indexColumn] : 0;
            }
        }
        public int GetRowSize() => sizeRows;
        public int getColSize() => sizeColumns;
        public static Matrix operator *(Matrix A, Matrix B)
        {
            Matrix C = new Matrix(A.GetRowSize(), B.getColSize());

            for (int i = 0; i < A.GetRowSize(); ++i)
            {
                for (int j = 0; j < B.getColSize(); ++j)
                {
                    for (int k = 0; k < A.getColSize(); ++k)
                    {
                        C[i, j] += A[i, k] * B[k, j];
                    }
                }
            }
            return C;
        }
        public void Print()
        {
            for (int i = 0; i < sizeRows; ++i)
            {
                for (int j = 0; j < sizeColumns; ++j)
                {
                    if (matrix[i, j] == int.MaxValue)
                        Console.Write("\u221e ");
                    else
                        Console.Write($"{matrix[i, j]} ");
                }
                Console.WriteLine();
            }
        }
        public void FillInf()
        {
            for (int i = 0; i < sizeRows; ++i)
            {
                for (int j = 0; j < sizeColumns; ++j)
                {
                    matrix[i, j] = int.MaxValue;
                }
            }

        }
        public int GetMaximalElement()
        {
            int maximal = matrix[0, 0];
            foreach (var value in matrix)
            {
                if (value > maximal)
                {
                    maximal = value;
                }
            }
            return maximal;
        }
        public int GetMaxInRow(int rowIndex)
        {
            int result = matrix[0, 0];
            for (int j = 0; j < sizeColumns; ++j)
            {
                if (matrix[rowIndex, j] > result)
                    result = matrix[rowIndex, j];
            }
            return result;
        }
        public bool ContainsInRow(int rowIndex, int value)
        {
            for (int j = 0; j < sizeColumns; ++j)
            {
                if (matrix[rowIndex, j] == value)
                    return true;
            }
            return false;
        }
    }
}