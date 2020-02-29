using System.Collections.Generic;

namespace LAB_4
{
    class Program
    {
        static void Main(string[] args)
        {
            Parser parser = new Parser("input.txt");
            (int n, int m, List<(int, int)> edgesList) = parser.GetInput();
            DirectedGraph graph = new DirectedGraph(n, m, edgesList);

            System.Console.Write("Do you want to work with file or console?(console/file) : ");
            string writeType = System.Console.ReadLine();

            if (writeType == "console")
            {
                GraphAlgorithm graphAlg = new GraphAlgorithm(graph, "console");
                graphAlg.PrintTolopologicalSort();
            }
            else
            {
                System.Console.Write("Type the name of output file : ");
                string fileName = System.Console.ReadLine();
                GraphAlgorithm graphAlg = new GraphAlgorithm(graph, "file", fileName);
                graphAlg.PrintTolopologicalSort();
            }
        }
    }
}
