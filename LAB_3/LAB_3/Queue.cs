using System.Collections.Generic;

namespace LAB_3
{
    class Queue
    {
        private readonly List<int> queue;

        public Queue() => queue = new List<int>();

        public void Enqueue(int item)
        {
            queue.Add(item);
        }

        public int Dequeue()
        {
            int toReturn = queue[0];
            queue.RemoveAt(0);
            return toReturn;
        }

        public int Peek() => queue[0];

        public int Count() => queue.Count;

        public List<int> ToList() => queue;
    }
}