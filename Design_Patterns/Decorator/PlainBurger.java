public class PlainBurger implements Burger {
 
    @Override
    public int getPrice() {
        return 1;
    }

    @Override
    public String getDescription() {
        return "Plain Burger";
    }


}
