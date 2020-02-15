using System.Collections.Generic;
using ClassMatrix;
using System;

namespace LAB_2
{
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
            switch(number)
            {
                case 1:
                    GetDistanceMatrix().Print();
                    break;
                case 2:
                    GetReachMatrix().Print();
                    break;
            }
        }
        protected  int EnterNumber(int down, int up)
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
            ToMultiple.Print();

            for (int i = 0; i < vertex_number; ++i)
            {
                FillPath(ref ResultMatrix, ToMultiple, i + 1);
                ToMultiple *= AdjacencyMatrix;
            }
            return ResultMatrix;
        }
        protected void FillReach(ref Matrix ToFill, Matrix A)
        {
            for(int i = 0; i < vertex_number; ++i)
            {
                for(int j = 0; j < vertex_number; ++j)
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

            for(int i = 0; i < vertex_number; ++i)
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
                WorkWithNumber(EnterNumber(down,up));
                Console.WriteLine("If you want to exit type 'exit' else press any key...");
                answer = Console.ReadLine();
            }
        }
    }
}
