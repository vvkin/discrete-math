using System.IO;

namespace LAB_4
{
    class Writer
    {
         private readonly string writeMode;
         private readonly string fileName;

        public Writer(string writeMode, string fileName = "output.txt")
        {
            this.writeMode = writeMode;
            this.fileName = (this.writeMode == "file") ? fileName : null;
            if (fileName != null)
            {
                using var cw = new StreamWriter("../../../" + fileName);
                cw.Write("");
            }
        }

        
        public void Write(string line = "")
        {
            if (writeMode == "console")
            {
                System.Console.Write(line);
            }
            else
            {
                using System.IO.StreamWriter cw = new System.IO.StreamWriter("../../../" + fileName, true);
                cw.Write(line);
            }
        }

        public void WriteLine(string line = "")
        {
            Write(line + "\n");
        }
    }
}
