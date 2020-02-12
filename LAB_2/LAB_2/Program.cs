using System;


class Program
{
    static void Main(string[] args)
    {
        Matrix a = new Matrix(3, 3);
        Matrix b = new Matrix(3, 3);
        for(int i = 0; i < a.getRowSize(); ++i)
        {
            for(int j = 0; j < a.getColSize(); ++j)
            {
                a[i, j] = 1;
                b[i, j] = 2;
            }
        }
        b ^= 3;
        b.Print();

    }
}

class Matrix
{
    private readonly int size_rows;
    private readonly int size_columns;
    private int[,] matrix;
    public Matrix(int n,int m){
        size_rows = (n >= 0) ? n : 0;
        size_columns = (m >= 0) ? m : 0;
        matrix = new int[size_rows, size_columns];
    }
    
    private bool NotOutOfTheRange(int row_index, int column_index){
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

        for (int k = 0; k < A.getRowSize(); ++k)
        {
            for(int i = 0; i < B.getColSize(); ++i)
            {
                for(int j = 0; j < A.getColSize(); ++j)
                {
                    C[k, i] += A[k, j] * B[j,i];
                }
            }
        }
        return C;
    }

    public static Matrix operator ^(Matrix A, int degree)
    {
        Matrix MultA = new Matrix(A.getRowSize(), A.getColSize());
        MultA = A;
        for(int i = 0; i < degree - 1; ++i)
        {
            MultA *= A;
        }
        return MultA;
    }

    public void Print()
    {
        for(int i = 0; i < size_rows; ++i)
        {
            for(int j = 0; j < size_columns; ++j)
            {
                System.Console.Write($"{matrix[i, j]} ");
            }
            System.Console.WriteLine();
        }
    }
}

