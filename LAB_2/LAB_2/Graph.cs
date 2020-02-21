using System.Collections.Generic;
using System;

namespace LAB_2
{
    class Graph
    {
        protected readonly int vertexNum;
        protected readonly int edgesNum;
        protected readonly List<(int, int)> edgesList;

        public Graph(int n, int m, List<(int, int)> edgesArray)
        {
            vertexNum = (n >= 0) ? n : 0;
            edgesNum = (m >= 0) ? m : 0;
            edgesList = edgesArray;
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
            Matrix adjacencyMatrix = new Matrix(vertexNum, vertexNum);

            foreach (var value in edgesList)
            {
                int start = value.Item1 - 1;
                int finish = value.Item2 - 1;
                adjacencyMatrix[start, finish] = 1;
                adjacencyMatrix[finish, start] = 1;
            }
            return adjacencyMatrix;
        }
        protected void FillPath(ref Matrix ToFill, Matrix A, int path_length)
        {
            for (int i = 0; i < A.GetRowSize(); ++i)
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
            Matrix resultMatrix = new Matrix(vertexNum, vertexNum);
            Matrix toMultiple = GetAdjacencyMatrix();
            Matrix adjacencyMatrix = GetAdjacencyMatrix();
            resultMatrix.FillInf();

            for (int i = 0; i < vertexNum; ++i)
            {
                FillPath(ref resultMatrix, toMultiple, i + 1);
                toMultiple *= adjacencyMatrix;
            }
            return resultMatrix;
        }
        protected void FillReach(ref Matrix ToFill, Matrix A)
        {
            for(int i = 0; i < vertexNum; ++i)
            {
                for(int j = 0; j < vertexNum; ++j)
                {
                    if ((i == j) || (A[i, j] != 0))
                        ToFill[i, j] = 1;
                }
            }
        }
        public Matrix GetReachMatrix()
        {
            Matrix reachMatrix = new Matrix(vertexNum, vertexNum);
            Matrix adjacencyMatrix = GetAdjacencyMatrix();
            Matrix toMultiple = GetAdjacencyMatrix();

            for(int i = 0; i < vertexNum; ++i)
            {
                FillReach(ref reachMatrix, toMultiple);
                toMultiple *= adjacencyMatrix;
            }
            return reachMatrix;
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
