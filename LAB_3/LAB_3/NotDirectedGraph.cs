using System.Collections.Generic;

namespace LAB_3
{
    class NotDirectedGraph
    {
        public int verticesNum { get; }
        private readonly int edgesNum;
        private readonly List<(int, int)> edgesList;

        public NotDirectedGraph(int n, int m, List<(int, int)> edgesArray)
        {
            verticesNum = (n >= 0) ? n : 0;
            edgesNum = (m >= 0) ? m : 0;
            edgesList = edgesArray;
        }

        public NotDirectedGraph(NotDirectedGraph graph)
        {
            verticesNum = graph.verticesNum;
            edgesNum = graph.edgesNum;
            edgesList = new List<(int, int)>(graph.edgesList);
        }

        public Dictionary<int, List<int>> GetAdjList()
        {
            Dictionary<int, List<int>> adjList = new Dictionary<int, List<int>>();
            
            for(int i = 0; i < verticesNum; ++i)
            {
                adjList.Add(i, new List<int>());
            }

            foreach(var edge in edgesList)
            {
                (int start, int finish) = (edge.Item1 - 1, edge.Item2 - 1);
                if (!adjList[start].Contains(finish))
                {
                    adjList[start].Add(finish);
                }
                if (!adjList[finish].Contains(start))
                {
                    adjList[finish].Add(start);
                }
            }
            foreach(var key in adjList.Keys)
            {
                adjList[key].Sort((a, b) => a.CompareTo(b));
            }
            return adjList;
        }
    }
}
