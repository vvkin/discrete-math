using System.Collections.Generic;

namespace LAB_4
{
    class GraphAlgorithm
    {
        private readonly Writer writer;
        private readonly DirectedGraph graph;

        public GraphAlgorithm(DirectedGraph graph, string writeMode, string fileName = null)
        {
            this.graph = new DirectedGraph(graph);
            writer = new Writer(writeMode, fileName);
        }

        private int[] TopologicalSort()
        {
            HashSet<int> visited = new HashSet<int>();
            int[] answer = new int[graph.verticesNum];
            Dictionary<int, List<int>> adjList = graph.GetAdjList();
            int currentPlace = graph.verticesNum;
            int humanIndex = 1;


            for (int vertex = 0; vertex < graph.verticesNum; ++vertex)
            {
                if (!visited.Contains(vertex))
                {
                    DFS(vertex);
                }
            }

            void DFS(int start)
            {
                visited.Add(start);
                
                foreach(var vertex in adjList[start])
                {
                    if (!visited.Contains(vertex))
                    {
                        DFS(vertex);
                    }
                }
                answer[--currentPlace] = start + humanIndex;
            }

            return answer;
        }

        public void PrintTolopologicalSort()
        {
            int[] result = TopologicalSort();
            
            foreach(var vertex in result)
            {
                writer.Write($"{vertex} ");
            }

            writer.Close();
        }
    }
}
