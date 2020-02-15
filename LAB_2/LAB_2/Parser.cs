using System.IO;
using System.Collections.Generic;
using System;

namespace LAB_2
{
    class Parser
    {
        private readonly StreamReader file;
        public Parser(string file_name)
        {
            string path = "../../../" + file_name;
            file = new StreamReader(path);
        }

        private (int, int) parseRow(string row)
        {
            string[] characters = row.Split(" ");
            int[] numbers = Array.ConvertAll(characters, s => int.Parse(s));
            return (numbers[0], numbers[1]);

        }

        public (int, int, List<(int, int)>) getInput()
        {
            string line = file.ReadLine();
            (int n, int m) = parseRow(line);
            List<(int, int)> edges_list = new List<(int, int)>();
            
            for(int i = 0; i < n; ++i)
            {
                line = file.ReadLine();
                if (line != null)
                    edges_list.Add(parseRow(line));
            }
            return (n, m, edges_list);
        }
    }
}
