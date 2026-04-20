import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class Connection {

    private Socket clientSocket; 
    private Boolean running; 
    private DataInputStream input;
    private DataOutputStream output;

    public Connection(Socket clientSocket) throws IOException {
        this.clientSocket = clientSocket;
        this.input = new DataInputStream(clientSocket.getInputStream());
        this.output = new DataOutputStream(clientSocket.getOutputStream());
    }

    public Socket getClienSocket() {
        return clientSocket;
    }

    public Boolean getRunning() {
        return running;
    }

    public synchronized void sentToClient(String message) throws Exception {
        output.writeUTF("-> echo: " + message);
    }

    public String receive() throws IOException {
        return input.readUTF();
    }
}
