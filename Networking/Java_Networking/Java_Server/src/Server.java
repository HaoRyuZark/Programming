import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.Executors;

public class Server {
    
    private static Server instance; 

    private int port; 
    private List<Connection> connections; 

    private Server(int port) {
        this.port = port;
        this.connections = new CopyOnWriteArrayList<>();
    }
    
    public static Server getInstance(int port) {
        
        if (instance == null) {
            Server.instance = new Server(port);
        }
        
        return Server.instance;
    }

    public void run() throws Exception {

        ServerSocket serverSocket = new ServerSocket(port); // bind to port 

        IO.println("Starting Server");

        try (var executor = Executors.newVirtualThreadPerTaskExecutor()) {
            
            while (true) {

                Socket socket = serverSocket.accept(); // open socket (fd) (blocking)

                if (socket == null) {
                    break;
                }

                Connection connection = new Connection(socket);
                connections.add(connection);

                executor.submit(() -> { 
                    handleConnection(connection); 
                });
            }
        } // executor waits for the tasks to complete
         
        serverSocket.close();
    
        IO.println("Closing Server");
    }

    public void setPort(int port) {
        this.port = port;
    }

    public int getPort() {
        return this.port;
    }

    private void handleConnection(Connection connection) {
        
        String in; 

        try { 
                while (true) {
                
                in = connection.receive();

                if (in.equals("\\exit")) {
                    connection.sentToClient(in); 
                    break;
                }
                else if (in.startsWith("\\broadc")) {
                    String outputString = in.substring("\\broadc".length());
                    broadcast(outputString, connection);
                } 
                else {
                    connection.sentToClient(in);
                }

            }
        } catch (Exception e) {
            System.out.println("Error in the IO System of the current connection");
        } 
    }

    private void broadcast(String outputString, Connection sender) throws Exception {
        for (Connection con: connections) {
            if (con == sender) { continue; }
            con.sentToClient(outputString);
        }
    }
}
