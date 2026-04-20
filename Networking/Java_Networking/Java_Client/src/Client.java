import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    public static final int CLIENT_PORT = 8080;

    public void run() throws Exception {

        Socket socket = new Socket("localhost", CLIENT_PORT); // non-blocking

        DataInputStream input = new DataInputStream(socket.getInputStream());
        DataOutputStream output = new DataOutputStream(socket.getOutputStream());

        String signal;
        Scanner scanner = new Scanner(System.in);

        IO.println("Connection stablished");

        Thread readerThread = Thread.ofVirtual().start(() -> {
            try {
                while (true) {
                    String in = input.readUTF(); // blocking
                    IO.println(in);
                }
            } catch (Exception e) {
                System.out.println("Error while reading");
            }
        });

        while (true) {
            
            IO.println("Enter a message or type \\exit to end connection");
            signal = scanner.nextLine();

            output.writeUTF(signal);

            if (signal.equals("\\exit")) {
                break;
            }
        }

        IO.println("Connection ending");

        socket.close();
        scanner.close();
        readerThread.interrupt();
    } 
    
}

