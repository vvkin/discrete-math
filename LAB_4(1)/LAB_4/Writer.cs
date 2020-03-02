namespace LAB_4
{
    class Writer
    {
        private readonly string writeMode;
        private readonly string fileName;
        private readonly System.IO.StreamWriter cw;

        public Writer(string writeMode, string fileName = "output.txt")
        {
            this.writeMode = writeMode;
            if (this.writeMode == "file")
            {
                this.fileName = fileName;
                this.cw = new System.IO.StreamWriter("../../../" + fileName);
                cw.Close();
                this.cw = new System.IO.StreamWriter("../../../" + fileName, true);
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
                cw.Write(line);
            }
        }

        public void WriteLine(string line = "")
        {
            Write(line + "\n");
        }

        public void Close()
        {
            if (writeMode != "console")
            {
                cw.Close();
            }
        }
    }
}
