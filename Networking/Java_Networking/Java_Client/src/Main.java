
public class Main {

    public static void main(String[] args) {
        
        Client cli = new Client();

        try {

            cli.run();

        } catch (Exception e) {
            IO.println("Something went wrong. Find it by yourself");
        }
 
       
    }
}