using System;
using System.Globalization;
using System.Text;

namespace ClassMatrix
{
    class Matrix
    {
        private readonly int size_rows;
        private readonly int size_columns;
        private int[,] matrix;
        public Matrix(int n, int m)
        {
            size_rows = (n >= 0) ? n : 0;
            size_columns = (m >= 0) ? m : 0;
            matrix = new int[size_rows, size_columns];
            Console.OutputEncoding = Encoding.Unicode;
        }
        private bool NotOutOfTheRange(int row_index, int column_index)
        {
            return (row_index >= 0 && row_index < size_rows) && (column_index >= 0 && column_index < size_columns);
        }
        public int this[int index_row, int index_column]
        {
            set
            {
                matrix[index_row, index_column] = (NotOutOfTheRange(index_row, index_column)) ? value : 0;
            }
            get
            {
                return (NotOutOfTheRange(index_row, index_column)) ? matrix[index_row, index_column] : 0;
            }
        }
        public int getRowSize()
        {
            return size_rows;
        }
        public int getColSize()
        {
            return size_columns;
        }
        public static Matrix operator *(Matrix A, Matrix B)
        {
            Matrix C = new Matrix(A.getRowSize(), B.getColSize());

            for (int i = 0; i < A.getRowSize(); ++i)
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
            for (int i = 0; i < size_rows; ++i)
            {
                for (int j = 0; j < size_columns; ++j)
                {
                    if (matrix[i, j] == int.MaxValue)
                        Console.Write("\u221e ");
                    else
                        System.Console.Write($"{matrix[i, j]} ");
                }
                System.Console.WriteLine();
            }
        }
        public void fillInf()
        {
            for (int i = 0; i < size_rows; ++i)
            {
                for (int j = 0; j < size_columns; ++j)
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
            for (int j = 0; j < size_columns; ++j)
            {
                if (matrix[rowIndex, j] > result)
                    result = matrix[rowIndex, j];
            }
            return result;
        }

        public bool ContainsInRow(int rowIndex, int value)
        {
            for (int j = 0; j < size_columns; ++j)
            {
                if (matrix[rowIndex, j] == value)
                    return true;
            }
            return false;
        }
    }
}