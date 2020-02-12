using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace WorkSpace
{
    class Program
    {
        public static void Main(string[] args)
        {
            Parser Info = new Parser("input.txt");
            (int n, int m, List<(int, int)> edges_list) = Info.getInput();
            System.Console.Write("Is you graph directed?(y/n) : ");
            string graphType = System.Console.ReadLine();

            if (graphType == "y")
            {
                DirectedGraph graph = new DirectedGraph(n, m, edges_list);
                graph.StartMenu();
            }
            else
            {
                NotDirectedGraph graph = new NotDirectedGraph(n, m, edges_list);
                graph.StartMenu();
            }
        }
    }

    class Parser
    {
        private readonly StreamReader file;
        public Parser(string file_name)
        {
            string path = "../../../" + file_name;
            file = new StreamReader(path);
        }

        private (int, int) parseRow(string row)
        {
            string[] characters = row.Split(" ");
            int[] numbers = Array.ConvertAll(characters, s => int.Parse(s));
            return (numbers[0], numbers[1]);

        }

        public (int, int, List<(int, int)>) getInput()
        {
            string line = file.ReadLine();
            (int n, int m) = parseRow(line);
            List<(int, int)> edges_list = new List<(int, int)>();

            for (int i = 0; i < n; ++i)
            {
                line = file.ReadLine();
                if (line != null)
                    edges_list.Add(parseRow(line));
            }
            return (n, m, edges_list);
        }
    }

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

    class Graph
    {
        protected readonly int vertex_number;
        protected readonly int edges_number;
        protected readonly List<(int, int)> edges_list;

        public Graph(int n, int m, List<(int, int)> edges_array)
        {
            vertex_number = (n >= 0) ? n : 0;
            edges_number = (m >= 0) ? m : 0;
            edges_list = edges_array;
        }
        protected virtual void ShowMenu()
        {
            Console.WriteLine("Choose one of the next options : ");
            Console.WriteLine("1 - Show distance matrix\n" +
                              "2 - Show reach matrix");
        }
        protected virtual void WorkWithNumber(int number)
        {
            switch (number)
            {
                case 1:
                    GetDistanceMatrix().Print();
                    break;
                case 2:
                    GetReachMatrix().Print();
                    break;
            }
        }
        protected int EnterNumber(int down, int up)
        {
            int number = 0;

            while (number > up || number < down)
            {
                Console.Write("\nType your choice : ");
                bool checker = int.TryParse(Console.ReadLine(), out number);
                if (number > up || number < down)
                    Console.WriteLine("Invalid input!");
            }
            return number;
        }
        protected virtual Matrix GetAdjacencyMatrix()
        {
            Matrix AdjacencyMatrix = new Matrix(vertex_number, vertex_number);

            foreach (var value in edges_list)
            {
                int start = value.Item1 - 1;
                int finish = value.Item2 - 1;
                AdjacencyMatrix[start, finish] = 1;
                AdjacencyMatrix[finish, start] = 1;
            }
            return AdjacencyMatrix;
        }
        protected void FillPath(ref Matrix ToFill, Matrix A, int path_length)
        {
            for (int i = 0; i < A.getRowSize(); ++i)
            {
                for (int j = 0; j < A.getColSize(); ++j)
                {
                    if (i == j)
                    {
                        ToFill[i, j] = 0;
                    }
                    else if ((ToFill[i, j] == int.MaxValue) && (A[i, j] != 0))
                    {
                        ToFill[i, j] = path_length;
                    }

                }
            }
        }
        protected Matrix GetDistanceMatrix()
        {
            Matrix ResultMatrix = new Matrix(vertex_number, vertex_number);
            Matrix ToMultiple = GetAdjacencyMatrix();
            Matrix AdjacencyMatrix = GetAdjacencyMatrix();
            ResultMatrix.fillInf();

            for (int i = 0; i < vertex_number; ++i)
            {
                FillPath(ref ResultMatrix, ToMultiple, i + 1);
                ToMultiple *= AdjacencyMatrix;
            }
            return ResultMatrix;
        }
        protected void FillReach(ref Matrix ToFill, Matrix A)
        {
            for (int i = 0; i < vertex_number; ++i)
            {
                for (int j = 0; j < vertex_number; ++j)
                {
                    if ((i == j) || (A[i, j] != 0))
                        ToFill[i, j] = 1;
                }
            }
        }
        protected Matrix GetReachMatrix()
        {
            Matrix ReachMatrix = new Matrix(vertex_number, vertex_number);
            Matrix AdjacencyMatrix = GetAdjacencyMatrix();
            Matrix ToMultiple = GetAdjacencyMatrix();

            for (int i = 0; i < vertex_number; ++i)
            {
                FillReach(ref ReachMatrix, ToMultiple);
                ToMultiple *= AdjacencyMatrix;
            }
            return ReachMatrix;
        }
        public virtual void StartMenu(int down, int up)
        {
            string answer = "";
            while (answer != "exit")
            {
                ShowMenu();
                WorkWithNumber(EnterNumber(down, up));
                Console.WriteLine("If you want to exit type 'exit' else press any key...");
                answer = Console.ReadLine();
            }
        }
    }

    class DirectedGraph : Graph
    {
        public DirectedGraph(int n, int m, List<(int, int)> edges_list) :
            base(n, m, edges_list)
        { }
        protected override Matrix GetAdjacencyMatrix()
        {
            Matrix AdjacencyMatrix = new Matrix(vertex_number, vertex_number);

            foreach (var value in edges_list)
            {
                int start = value.Item1 - 1;
                int finish = value.Item2 - 1;
                AdjacencyMatrix[start, finish] = 1;
            }
            return AdjacencyMatrix;
        }
        protected override void ShowMenu()
        {
            base.ShowMenu();
            Console.Write("3 - Show type of connectivity");
        }
        protected override void WorkWithNumber(int number)
        {
            base.WorkWithNumber(number);
            switch (number)
            {
                case 3:
                    Console.WriteLine($"Graph is {GetConnectedType()}");
                    break;
            }
        }
        public void StartMenu() => base.StartMenu(1, 3);

        protected bool IsStrongConnected()
        {
            Matrix reachMatrix = GetReachMatrix();
            int count = 0;
            for (int i = 0; i < vertex_number; ++i)
            {
                for (int j = 0; j < i; ++j)
                {
                    if (reachMatrix[i, j] == reachMatrix[j, i] && reachMatrix[i, j] == 1)
                    {
                        ++count;
                    }
                }
            }
            return (count == vertex_number);
        }

        protected bool IsOneSideConnected()
        {
            Matrix reachMatrix = GetReachMatrix();

            for (int i = 0; i < vertex_number; ++i)
            {
                for (int j = 0; j < vertex_number; ++j)
                {
                    if (reachMatrix[i, j] != 1 && reachMatrix[j, i] != 1)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        protected void MakeNotDirected(ref Matrix A)
        {
            for (int i = 0; i < A.getRowSize(); ++i)
            {
                for (int j = 0; j < A.getColSize(); ++j)
                {
                    if (A[i, j] == 1)
                        A[j, i] = 1;
                }
            }
        }
        protected bool IsWeaklyConnected()
        {
            Matrix reachMatrix = GetReachMatrix();
            MakeNotDirected(ref reachMatrix);

            for (int i = 0; i < vertex_number; ++i)
            {
                for (int j = 0; j < vertex_number; ++j)
                {
                    if (reachMatrix[i, j] != 1)
                        return false;
                }
            }
            return true;
        }
        protected string GetConnectedType()
        {
            if (IsStrongConnected()) return "strong connected";
            if (IsOneSideConnected()) return "one side connected";
            if (IsWeaklyConnected()) return "weakly connected";
            return "incorehent";
        }
    }

    class NotDirectedGraph : Graph
    {
        public NotDirectedGraph(int n, int m, List<(int, int)> edges_list) :
            base(n, m, edges_list)
        { }

        protected int GetRadius()
        {
            Matrix distanceMatrix = GetDistanceMatrix();
            int Radius = distanceMatrix.GetMaxInRow(0);

            for (int i = 1; i < vertex_number; ++i)
            {
                int currentEccentricity = distanceMatrix.GetMaxInRow(i);
                if (currentEccentricity < Radius)
                {
                    Radius = currentEccentricity;
                }
            }
            return Radius;
        }
        protected int GetDiameter()
        {
            Matrix distanceMatrix = GetDistanceMatrix();
            return distanceMatrix.GetMaximalElement();
        }
        protected List<int> GetCenter()
        {
            int Radius = GetRadius();
            Matrix distanceMatrix = GetDistanceMatrix();
            List<int> centresList = new List<int>();
            for (int i = 0; i < vertex_number; ++i)
            {
                int currentEccentricity = distanceMatrix.GetMaxInRow(i);
                if (currentEccentricity == Radius)
                    centresList.Add(i + 1);
            }
            return centresList;
        }
        protected override Matrix GetAdjacencyMatrix() => base.GetAdjacencyMatrix();
        protected List<int> GetDistances()
        {
            List<int> distances = new List<int>();
            Matrix distanceMatrix = GetDistanceMatrix();

            for (int i = 0; i < vertex_number; ++i)
            {
                for (int j = 0; j < vertex_number; ++j)
                {
                    if (!distances.Contains(distanceMatrix[i, j]))
                    {
                        distances.Add(distanceMatrix[i, j]);
                    }
                }
            }
            return distances;
        }
        protected void PrintStoreys()
        {
            List<int> distances = GetDistances();
            Matrix distancesMatrix = GetDistanceMatrix();
            distances.Sort();

            foreach (var value in distances)
            {
                List<int> temp = new List<int>();
                for (int i = 0; i < vertex_number; ++i)
                {
                    if (distancesMatrix.ContainsInRow(i, value))
                    {
                        temp.Add(i);
                    }
                }
                if (value != Int32.MaxValue)
                    Console.Write($"Distance = {value} : ");
                else
                    Console.Write("Distance = \u221e : ");
                temp.ForEach(el => Console.Write($"{el} "));
                Console.WriteLine();
            }
        }
        protected override void ShowMenu()
        {
            Console.WriteLine("Choose one of the next options : ");
            Console.WriteLine("1 - Show distance matrix\n" +
                "2 - Show reach matrix\n" +
                "3 - Show graph`s diameter\n" +
                "4 - Show graph`s radius\n" +
                "5 - Show central vertex(vertices)\n" +
                "6 - Show storeys of graph\n");
        }
        protected override void WorkWithNumber(int number)
        {
            base.WorkWithNumber(number);
            switch (number)
            {
                case 3:
                    int Diameter = GetDiameter();
                    if (Diameter != int.MaxValue)
                        Console.WriteLine($"Diameter = {Diameter}");
                    else
                        Console.WriteLine("Diameter = \u221e ");
                    break;
                case 4:
                    int Radius = GetRadius();
                    if (Radius != Int32.MaxValue)
                        Console.WriteLine($"Radius = {Radius}");
                    else
                        Console.WriteLine("Radius = \u221e ");
                    break;
                case 5:
                    GetCenter().ForEach(el => Console.Write($"{el} "));
                    Console.WriteLine();
                    break;
                case 6:
                    PrintStoreys();
                    break;
            }
        }
        public void StartMenu()
        {
            base.StartMenu(1, 6);
        }
    }
}
