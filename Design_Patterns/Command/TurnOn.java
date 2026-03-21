
public class TurnOn implements Command {
  
  private Bulb receiver;

  public TurnOn(Bulb bulb) {
    this.receiver = bulb;
  }

  void execute() {
    System.out.println("Turning on")
  }
}
