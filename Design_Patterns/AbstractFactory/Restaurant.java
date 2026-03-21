
public abstract class Restaurant {
    
    public Burger orderBurger() {
        Burger burger = createBurger();
        burger.burgir();
        return burger;
    }
    
    // We can also declare more createProduct methods for each of the interfaces 
    // of our abstract products
    public abstract Burger createBurger();
}
