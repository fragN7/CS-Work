using System.Net;
using System.Text;
using System.Threading;

namespace FutureTPL
{
    public class Socket
    {
        // event atomic variables needed for task implementations
        public ManualResetEvent connectDone = new ManualResetEvent(false);
        public ManualResetEvent sendDone = new ManualResetEvent(false);
        public ManualResetEvent receiveDone = new ManualResetEvent(false);

        public Socket sock = null; // socket to connect to server

        public const int BUFF_SIZE = 1024; // 1024 bytes 

        public byte[] buffer = new byte[BUFF_SIZE]; 

        public StringBuilder responseContent = new StringBuilder();

        public int id; // keep a unique id for each custom socket
        public string hostname; 
        public string endpoint; 

        public IPEndPoint remoteEndPoint; // address + port 
    }
}