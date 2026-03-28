
public class BeefDecorator extends BurgerDecorator {

    public BeefDecorator(Burger burger) {
        super(burger);
    }


    @Override
    public int getPrice() {
        return decoratedBurger.getPrice() + 1;
    }

    @Override
    public String getDescription() {
        return decoratedBurger.getDescription() + ", Veggie";
    }
}
