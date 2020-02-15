using System;
using System.Collections.Generic;
using System.Text;
using ClassMatrix;

namespace LAB_2
{
    class NotDirectedGraph : Graph
    {
        public NotDirectedGraph(int n, int m, List<(int, int)> edges_list) :
            base(n, m, edges_list) { }
        
        protected int GetRadius()
        {
            Matrix distanceMatrix = GetDistanceMatrix();
            int Radius = distanceMatrix.GetMaxInRow(0);

            for(int i = 1; i < vertex_number; ++i)
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
            
            for(int i = 0; i < vertex_number; ++i)
            {
                for(int j = 0; j < vertex_number; ++j)
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

            foreach(var value in distances)
            {
                List<int> temp = new List<int>();
                for(int i = 0; i < vertex_number; ++i)
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
            switch(number)
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
