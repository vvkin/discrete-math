using LAB_2;
using System.IO;
using System.Collections.Generic;
using ClassMatrix;

class ProgramV2
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




