public class IdleState implements CoffeeMachineState {

  private CoffeeMachine coffeeMachine;
  
  public IdleState(CoffeeMachine coffeeMachine) {
    this.coffeeMachine = coffeeMachine
  }
 
  @Override
  public void insertCoin() {
    System.out.println("Coin inserted");
    coffeeMachine.setState(coffeeMachine.getSelectingState());
  }

  @Override
  public void dispendCoffee() {
    System.out.println("Sike");
  }

  @Override
  public void selectCoffee() {
    System.out.println("Sike");
  }
}
