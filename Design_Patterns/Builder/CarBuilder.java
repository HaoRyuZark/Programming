
public class CarBuilder {
    
    private Car car;

    public void CarBuilder(){
        this.car = new Car();
    }

    public void brand(String brand) {
        car.setBrand(brand);
    }

    public void color(String color) {
        car.setColor(color);
    }

    public void model(String model) {
        car.setModel(model);
    }
    
    public Car build() {
       return this.car; 
    }

}
