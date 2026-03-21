
public class Car {

    private int brand;
    private String color;
    private String model;

    public Car() {}
    
    public Car(String brand, String color, String model) {
        this.brand = brand;
        this.color = color;
        this.model = model;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getBrand() {
        return this.brand;
    }

    public String getColor() {
        return this.color;
    }

    public String getModel() {
        return this.model;
    }
}
