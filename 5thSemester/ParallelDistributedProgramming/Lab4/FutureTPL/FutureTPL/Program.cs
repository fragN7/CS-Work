namespace FutureTPL
{
    using System;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

class Program
{
    static async Task Main(string[] args)
    {
        await DownloadFilesAsync();
    }

    static async Task DownloadFilesAsync()
    {
        string[] urls = { "http://example.com/file1.txt", "http://example.com/file2.txt", "http://example.com/file3.txt" };

        foreach (var url in urls)
        {
            await DownloadFileAsync(url);
        }
    }

    static async Task DownloadFileAsync(string url)
    {
        Uri uri = new Uri(url);
        using (Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
        {
            await socket.ConnectAsync(uri.Host, 80);

            string request = $"GET {uri.PathAndQuery} HTTP/1.1\r\nHost: {uri.Host}\r\nConnection: close\r\n\r\n";
            byte[] requestData = Encoding.ASCII.GetBytes(request);
            await SendAsync(socket, requestData);

            string httpResponse = await ReceiveAsync(socket);
            Console.WriteLine($"Received response for {uri}: {httpResponse}");

            // Parse httpResponse for Content-Length header
            int contentLength = ParseContentLength(httpResponse);

            // Now read the file content
            byte[] fileData = await ReadFileContentAsync(socket, contentLength);
            // Do something with the file content (fileData)
        }
    }

    static async Task SendAsync(Socket socket, byte[] data)
    {
        await Task.Factory.FromAsync(
            socket.BeginSend,
            socket.EndSend,
            data,
            0,
            data.Length,
            SocketFlags.None,
            null);
    }

    static async Task<string> ReceiveAsync(Socket socket)
    {
        byte[] buffer = new byte[1024];
        int received = await Task<int>.Factory.FromAsync(
            socket.BeginReceive,
            socket.EndReceive,
            buffer,
            0,
            buffer.Length,
            SocketFlags.None,
            null);

        return Encoding.ASCII.GetString(buffer, 0, received);
    }

    static int ParseContentLength(string response)
    {
        const string contentLengthHeader = "Content-Length: ";
        int contentLengthIndex = response.IndexOf(contentLengthHeader, StringComparison.OrdinalIgnoreCase);
        if (contentLengthIndex >= 0)
        {
            int startIndex = contentLengthIndex + contentLengthHeader.Length;
            int endIndex = response.IndexOf("\r\n", startIndex);
            if (endIndex >= 0)
            {
                string lengthString = response.Substring(startIndex, endIndex - startIndex);
                if (int.TryParse(lengthString, out int contentLength))
                {
                    return contentLength;
                }
            }
        }
        return -1;
    }

    static async Task<byte[]> ReadFileContentAsync(Socket socket, int contentLength)
    {
        byte[] fileData = new byte[contentLength];
        int received = 0;
        while (received < contentLength)
        {
            int bytesToReceive = Math.Min(contentLength - received, 1024);
            byte[] buffer = new byte[bytesToReceive];
            int bytesRead = await Task<int>.Factory.FromAsync(
                socket.BeginReceive,
                socket.EndReceive,
                buffer,
                0,
                buffer.Length,
                SocketFlags.None,
                null);

            if (bytesRead == 0)
            {
                // Handle premature connection close or other errors
                break;
            }

            Buffer.BlockCopy(buffer, 0, fileData, received, bytesRead);
            received += bytesRead;
        }

        return fileData;
    }
}

}