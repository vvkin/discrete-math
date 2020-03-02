using System.Collections.Generic;

namespace LAB_3
{
    class GraphAlgorithm
    {
        private readonly Writer writer;
        private readonly NotDirectedGraph graph;

        public GraphAlgorithm(NotDirectedGraph graph, string writeMode, string fileName = null)
        {
            this.graph = new NotDirectedGraph(graph);
            writer = new Writer(writeMode, fileName);
        }

        private void ShowMenu()
        {
            System.Console.WriteLine("Choose one of the next options\n" +
                "1 - DFS\n" +
                "2 - BFS");
        }

        private int EnterNumber(int up)
        {
            int number = 0;

            while (number > up || number < 1)
            {
                System.Console.Write("Type your choice : ");
                _ = int.TryParse(System.Console.ReadLine(), out number);
                if (number > up || number < 1)
                    System.Console.WriteLine("Invalid input!");
            }
            return number;
        }

        private void WorkWithNumber(int number)
        {
            switch(number)
            {
                case 1:
                    System.Console.WriteLine("\nWhich vertex is the starting point?");
                    DFS(EnterNumber(graph.verticesNum));
                    break;
                case 2:
                    System.Console.WriteLine("\nWhich vertex is the starting point?");
                    BFS(EnterNumber(graph.verticesNum));
                    break;
            }
        }

        public void StartMenu()
        {
            string answer = "";
            while (answer != "exit")
            {
                ShowMenu();
                WorkWithNumber(EnterNumber(2));
                System.Console.WriteLine("If you want to exit type 'exit' else press any key...");
                answer = System.Console.ReadLine();
                writer.WriteLine();
            }
            writer.Close();
        }

        private void ShowTable(int vertex, int bfsNum)
        {
            writer.Write($"   {vertex + 1}   |  {bfsNum}  | ");
        }

        private void PrintList(List<int> toPrint)
        {
            foreach(var value in toPrint)
            {
                writer.Write($"{value + 1} ");
            }
            writer.WriteLine();
        }

        private void BFS(int start)
        {
            Dictionary<int, List<int>> adjList = graph.GetAdjList();
            Queue queue = new Queue();
            HashSet<int> visited = new HashSet<int>();
            int k = 0;
            int humanIndex = 1;
            start -= humanIndex;

            writer.WriteLine("Vertex | BFS | QUEUE");

            queue.Enqueue(start);
            visited.Add(start);
            ShowTable(start, ++k);
            PrintList(queue.ToList());

            while (queue.Count() != 0)
            {
                start = queue.Peek();

                foreach (var vertex in adjList[start])
                {
                    if (!visited.Contains(vertex))
                    {
                        queue.Enqueue(vertex);
                        visited.Add(vertex);
                        ShowTable(vertex, ++k);
                        PrintList(queue.ToList());
                    }
                }
                start = queue.Dequeue();
                writer.Write($"   -   |  -  | ");
                PrintList(queue.ToList());

            }
        }

        private void DFS(int start)
        {
            Dictionary<int, List<int>> adjList = graph.GetAdjList();
            Stack stack = new Stack();
            HashSet<int> visited = new HashSet<int>();
            int k = 0;
            int humanIndex = 1;
            start -= humanIndex;

            writer.WriteLine("Vertex | DFS | Stack");

            stack.Push(start);
            visited.Add(start);
            ShowTable(start, ++k);
            PrintList(stack.ToList());

            DoWork(start);

            writer.WriteLine("   -   |  -  | ");

            void DoWork(int start)
            {
                foreach (var vertex in adjList[start])
                {
                    if (!visited.Contains(vertex))
                    {
                        stack.Push(vertex);
                        visited.Add(vertex);
                        ShowTable(vertex, ++k);
                        PrintList(stack.ToList());
                        DoWork(vertex);

                        if (stack.Count() == 0) return;
                        int stackHead = stack.Pop();
                        writer.Write("   -   |  -  | ");
                        PrintList(stack.ToList());
                        DoWork(stackHead);
                    }
                }
                
            }
        }
    }
}
