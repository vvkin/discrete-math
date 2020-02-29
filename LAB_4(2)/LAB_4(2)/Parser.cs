using System.IO;
using System.Collections.Generic;
using System;

namespace LAB_4_2_
{
    class Parser
    {
        private readonly StreamReader file;
        public Parser(string fileName)
        {
            string path = "../../../" + fileName;
            file = new StreamReader(path);
        }

        private (int, int) ParseRow(string row)
        {
            string[] characters = row.Split(" ");
            int[] numbers = Array.ConvertAll(characters, s => int.Parse(s));
            return (numbers[0], numbers[1]);

        }

        public (int, int, List<(int, int)>) GetInput()
        {
            string line = file.ReadLine();
            (int n, int m) = ParseRow(line);
            List<(int, int)> edgesList = new List<(int, int)>();

            for (int i = 0; i < m; ++i)
            {
                line = file.ReadLine();
                if (line != null)
                    edgesList.Add(ParseRow(line));
            }
            return (n, m, edgesList);
        }
    }
}
