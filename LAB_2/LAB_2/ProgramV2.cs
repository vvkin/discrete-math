using LAB_2;
using System.Collections.Generic;

class ProgramV2
{
    public static void Main(string[] args)
    {
        Parser Info = new Parser("input.txt");
        (int vertexNum, int edgesNum, List<(int, int)> edgesList) = Info.GetInput();

        System.Console.Write("Is your graph directed?(y/n) : ");
        string graphType = System.Console.ReadLine();

        if (graphType == "y")
        {
            DirectedGraph graph = new DirectedGraph(vertexNum, edgesNum, edgesList);
            graph.StartMenu();
        }
        else
        {
            NotDirectedGraph graph = new NotDirectedGraph(vertexNum, edgesNum, edgesList);
            graph.StartMenu();
        }
    }
}




