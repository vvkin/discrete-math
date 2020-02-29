using System.Collections.Generic;

namespace LAB_4_2_
{
    class DirectedGraph
    {
        public int verticesNum { get; }
        private readonly int edgesNum;
        private List<(int, int)> edgesList;

        public DirectedGraph(int n, int m, List<(int, int)> edgesArray)
        {
            verticesNum = (n >= 0) ? n : 0;
            edgesNum = (m >= 0) ? m : 0;
            edgesList = edgesArray;
        }

        public DirectedGraph(DirectedGraph graph)
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
            }
            foreach(var key in adjList.Keys)
            {
                adjList[key].Sort((a, b) => a.CompareTo(b));
            }
            return adjList;
        }

        public void Transpose()
        {
            List<(int, int)> transposedList = new List<(int, int)>();
            
            foreach(var edge in edgesList)
            {
                transposedList.Add((edge.Item2, edge.Item1));
            }

            edgesList = new List<(int, int)>(transposedList);
        }
    }
}
