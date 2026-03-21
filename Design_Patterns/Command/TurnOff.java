
public class TurnOff implements Command {
  
  private Bulb receiver;

  public TurnOff(Bulb bulb) {
    this.receiver = bulb;
  }

  void execute() {
    System.out.println("Turning off")
  }
}


