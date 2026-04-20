
public class Main {

    public static final int SERVER_PORT = 8080;

    public static void main(String[] args) {
        
        Server server = Server.getInstance(SERVER_PORT);

        try {

            server.run();

        } catch (Exception e) {
            IO.println("Something went wrong. Find it by yourself");
        }
         
    }
}