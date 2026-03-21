
public class SelectingState implements CoffeeMachineState {

  private CoffeeMachine coffeeMachine;
  
  public SelectingState(CoffeeMachine coffeeMachine) {
    this.coffeeMachine = coffeeMachine
  }
 
  @Override
  public void insertCoin() {
    System.out.println("Sike");
  }

  @Override
  public void dispendCoffee() {
    System.out.println("Sike");
  }

  @Override
  public void selectCoffee() {
    System.out.println("Coffee selected");
    coffeeMachine.setState(coffeeMachine.getDispensingState());
  }

}


