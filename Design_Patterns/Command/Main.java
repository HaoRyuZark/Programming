
public class Main {

  public static void main(String[] args) {

      Bulb bulb = new Bulb();
      
      Command turnOff = new TurnOff(bulb);
      Command turnOn = new TurnOn(bulb);

      RemoteControl remoteControl = new RemoteControl();

      remoteControl.submit(turnOn);
      remoteControl.submit(turnOff);
  }
}
