public class AmazonBox implements Box {
    
    private List<Box> boxes; 
    private Product product;

    @Override
    public void load(Product product) {
        this.product = product;
    }
    
    public int calculatePrice() {
        return traverse(this); 
    }

    private int traverse(Box box) {
        
        if (box.boxes.isEmpty()) {
            return product.getPrice();
        }
        
        int sum = 0;
        for (Box box: boxes) {
            sum += traverse(box);
        }

        return sum;
    }
}
