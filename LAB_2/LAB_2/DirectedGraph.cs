using System;
using System.Collections.Generic;
using System.Text;
using ClassMatrix;

namespace LAB_2
{
    class DirectedGraph : Graph
    {
        public DirectedGraph(int n, int m, List<(int, int)> edges_list) :
            base(n, m, edges_list){ }
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
                for(int j = 0; j < i; ++j)
                {
                    if (reachMatrix[i, j] == reachMatrix[j,i] && reachMatrix[i, j] == 1)
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
            
            for(int i = 0; i < vertex_number; ++i)
            {
                for(int j = 0; j < vertex_number; ++j)
                {
                    if (reachMatrix[i, j] != 1 && reachMatrix[j ,i] != 1)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        protected void MakeNotDirected(ref Matrix A)
        {
            for(int i = 0; i < A.getRowSize(); ++i)
            {
                for(int j = 0; j < A.getColSize(); ++j)
                {
                    if (A[i, j] == 1)
                        A[j, i] = 1;
                }
            }
        }
        protected bool  IsWeaklyConnected()
        {
            Matrix reachMatrix = GetReachMatrix();
            MakeNotDirected(ref reachMatrix);

            for(int i = 0; i < vertex_number; ++i)
            {
                for(int j = 0; j < vertex_number; ++j)
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
