using System;
using System.Collections.Generic;

namespace LAB_2
{
    class NotDirectedGraph : Graph
    {
        public NotDirectedGraph(int n, int m, List<(int, int)> edgesList) :
            base(n, m, edgesList) { }
        
        protected int GetRadius()
        {
            Matrix distanceMatrix = GetDistanceMatrix();
            int radius = distanceMatrix.GetMaxInRow(0);

            for(int i = 1; i < vertexNum; ++i)
            {
                int currentEccentricity = distanceMatrix.GetMaxInRow(i);
                if (currentEccentricity < radius)
                {
                    radius = currentEccentricity;
                }
            }
            return radius;
        }
        protected int GetDiameter()
        {
            Matrix distanceMatrix = GetDistanceMatrix();
            return distanceMatrix.GetMaximalElement();
        }
        protected List<int> GetCenter()
        {
            int radius = GetRadius();
            Matrix distanceMatrix = GetDistanceMatrix();
            List<int> centresList = new List<int>();
            for (int i = 0; i < vertexNum; ++i)
            {
                int currentEccentricity = distanceMatrix.GetMaxInRow(i);
                if (currentEccentricity == radius)
                    centresList.Add(i + 1);
            }
            return centresList;
        }
        protected override Matrix GetAdjacencyMatrix() => base.GetAdjacencyMatrix();
        protected List<int> GetDistances()
        {
            List<int> distances = new List<int>();
            Matrix distanceMatrix = GetDistanceMatrix();
            
            for(int i = 0; i < vertexNum; ++i)
            {
                for(int j = 0; j < vertexNum; ++j)
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
                for(int i = 0; i < vertexNum; ++i)
                {
                    if (distancesMatrix.ContainsInRow(i, value))
                    {
                        temp.Add(i + 1);
                    }
                }
                if (value != int.MaxValue)
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
                    int diameter = GetDiameter();
                    if (diameter != int.MaxValue)
                        Console.WriteLine($"Diameter = {diameter}");
                    else
                        Console.WriteLine("Diameter = \u221e ");
                    break;
                case 4:
                    int radius = GetRadius();
                    if (radius != int.MaxValue)
                        Console.WriteLine($"Radius = {radius}");
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
