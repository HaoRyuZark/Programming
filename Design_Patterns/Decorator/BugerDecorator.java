
public abstract class BurgerDecorator implements Burger {

    protected Burger decoratedBurger; 

    public BurgerDecorator(Burger decoratedBurger) {
        this.decoratedBurger = decoratedBurger;
    }
     
    @Override
    public int getPrice() {
        return decoratedBurger.getPrice();
    }

    @Override
    public String getDescription() {
        return decoratedBurger.getDescription();
    }

   
    

}
