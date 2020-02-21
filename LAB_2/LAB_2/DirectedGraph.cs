using System;
using System.Collections.Generic;

namespace LAB_2
{
    class DirectedGraph : Graph
    {
        public DirectedGraph(int n, int m, List<(int, int)> edges_list) :
            base(n, m, edges_list){ }
        protected override Matrix GetAdjacencyMatrix()
        {
            Matrix adjacencyMatrix = new Matrix(vertexNum, vertexNum);

            foreach (var value in edgesList)
            {
                int start = value.Item1 - 1;
                int finish = value.Item2 - 1;
                adjacencyMatrix[start, finish] = 1;
            }
            return adjacencyMatrix;
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

            for (int i = 0; i < vertexNum; ++i)
            {
                for(int j = 0; j < vertexNum; ++j)
                {
                    if (reachMatrix[i, j] != 1 || reachMatrix[j, i] != 1)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        protected bool IsOneSideConnected()
        {
            Matrix reachMatrix = GetReachMatrix();
            
            for(int i = 0; i < vertexNum; ++i)
            {
                for(int j = 0; j < vertexNum; ++j)
                {
                    if (reachMatrix[i, j] != 1 && reachMatrix[j, i] != 1)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        protected bool IsWeaklyConnected()
        {
            Graph A = new Graph(vertexNum, edgesNum, edgesList);
            Matrix reachMatrix = A.GetReachMatrix();
           
            for(int i = 0; i < vertexNum; ++i)
            {
                for(int j = 0; j < vertexNum; ++j)
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
}
