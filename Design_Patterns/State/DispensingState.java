
public class DispensingState implements CoffeeMachineState {

  private CoffeeMachine coffeeMachine;
  
  public DispensingState(CoffeeMachine coffeeMachine) {
    this.coffeeMachine = coffeeMachine
  }

  @Override
  public void insertCoin() {
    System.out.println("Sike");
  }

  @Override
  public void dispendCoffee() {
    System.out.println("Coffe dispensed");
    coffeeMachine.setState(coffeeMachine.getIdleState());
  }

  @Override
  public void selectCoffee() {
    System.out.println("Sike");
  }
}
