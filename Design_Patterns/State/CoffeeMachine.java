
public class CoffeeMachine {
 
  private CoffeeMachineState idleState;
  private CoffeeMachineState selectingState;
  private CoffeeMachineState dispensingState;

  private CoffeeMachineState current;
  
  public CoffeeMachine() {
    
    idleState = new IdleState(this);
    selectingState = new SelectingState(this);
    dispensingState = new DispensingState(this);
   
    current = this.idleState;
  }

  public void setState(CoffeeMachineState state) {
    current = state;
  }

  public void insertCoin() {
    state.insertCoin();
  }

  public void selectCoffee() {
    state.selectCoffee();
  }

  public void dispendCoffee() {
    state.dispendCoffee();
  }

}
