using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace LAB_8_1_
{
    class Edge
    {
        public int dest, flow, pred;
        public Edge(int dest, int flow, int pred = -1)
        {
            this.dest = dest;
            this.flow = flow;
            this.pred = pred;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            var adjL = GetInput("input.txt");
        }

        static Dictionary<int, List<Edge>> GetInput(string fileName)
        {
            string path = "../../../" + fileName;
            using (var sr = new StreamReader(path))
            {
                var fisrstRow = sr.ReadLine().Split().ToList().ConvertAll(s => int.Parse(s));
                (var vNum, var eNum) = (fisrstRow[0], fisrstRow[1]);
                var adjL = new Dictionary<int, List<Edge>>(vNum);
                for (var i = 0; i < vNum; ++i) adjL[i] = new List<Edge>();

                for(var i = 0; i < eNum; ++i)
                {
                    (var start, var end, var flow) = ParseRow(sr.ReadLine());
                    adjL[start - 1].Add(new Edge(end - 1, flow));
                }
                return adjL;
            }
        }

        static (int,int, int) ParseRow(string row)
        {
            var nums = row.Split().ToList().ConvertAll(s => int.Parse(s));
            return (nums[0], nums[1], nums[2]);
        }


        static (int, int) GetSourceAndSick(Dictionary<int, List<Edge>> adjL)
        {
            var inDegree = new int[adjL.Count];
            var outDegree = new int[adjL.Count];
            for(var i = 0; i < adjL.Count; ++i)
            {
                outDegree[i] = adjL[i].Sum(s => s.flow);
                foreach(var edge in adjL[i])
                {
                    
                }
            }
        }

        static (int[], int[]) GetDegrees(Dictionary<int, List<Edge>>)
        {

        }


        static void ProcessFulkerson(Dictionary<int, List<Edge>> startFlows)
        {
            var adjL = new Dictionary<int, List<Edge>>(startFlows);
        }

    }
}
