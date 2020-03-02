using System.Collections.Generic;

namespace LAB_3
{
    class Stack
    {
        private List<int> stack;

        public Stack() => stack = new List<int>();

        public int Pop()
        {
            int toReturn = stack[stack.Count - 1];
            stack.RemoveAt(stack.Count - 1);
            return toReturn;
        }

        public void Push(int item) => stack.Add(item);

        public int Peek() => stack[stack.Count - 1];

        public int Count() => stack.Count;

        public List<int> ToList() => stack;
    }
}
