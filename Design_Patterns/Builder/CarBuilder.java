
public class CarBuilder {
    
    private Car car;

    public CarBuilder(){
        this.car = new Car();
    }

    public CarBuilder brand(String brand) {
        car.setBrand(brand);
        return this;
    }

    public CarBuilder color(String color) {
        car.setColor(color);
        return this;
    }

    public CarBuilder model(String model) {
        car.setModel(model); 
        return this;
    }
    
    public Car build() {
       return this.car; 
    }

}
