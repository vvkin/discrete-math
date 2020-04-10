using System.Collections.Generic;

namespace LAB_4_2_
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


            for(int vertex = 0; vertex < graph.verticesNum; ++vertex)
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
                answer[--currentPlace] = start;
            }
            return answer;
        }


        private List<List<int>> GetConnectComponents()
        {
            int[] sortedVertices = TopologicalSort();
            graph.Transpose();
            Dictionary<int, List<int>> adjList = graph.GetAdjList();
            HashSet<int> visited = new HashSet<int>();
            List<int> component = new List<int>();
            List<List<int>> componentsList = new List<List<int>>();
            int humanIndex = 1;

            foreach(var vertex in sortedVertices)
            {
                if (!visited.Contains(vertex))
                {
                    DFS(vertex);
                }
                if (component.Count != 0)
                {
                    componentsList.Add(new List<int>(component));
                    component.Clear();
                }
            }

            void DFS(int start)
            {
                visited.Add(start);
                component.Add(start + humanIndex);

                foreach(var vertex in adjList[start])
                {
                    if (!visited.Contains(vertex))
                    {
                        DFS(vertex);
                    }
                }
            }

            return componentsList;
        }

        public void PrintStrongConnectedComponents()
        {
            List<List<int>> componetsList = GetConnectComponents();

            writer.WriteLine($"\nThe number of strongly connected components is equal to {componetsList.Count}");
            writer.WriteLine("Componets : ");

            foreach(var component in componetsList)
            {
                component.Sort();
                foreach(var vertex in component)
                {
                    writer.Write($"{vertex} ");
                }
                writer.WriteLine();
            }

            writer.Close();
        }
    }
}
