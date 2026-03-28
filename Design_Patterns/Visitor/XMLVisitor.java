public class XMLVisitor extends Visitor {
    
    public void exportCity(City city) {
        visitCity(city);
    }

    public void exportountry(Country country) {
        visitCountry(country);
    }
   
    public void exportContinent(Continent continent) {
        visitContinent(continent);
    }
   
    public void exportPark(Park park) {
        visitPark(park);
    }

    @Override
    protected void visitCity(City city) {
        System.out.println("Stuff");
    }

    @Override
    protected void visitCountry(Country country){
        System.out.println("Stuff");
    } 

    @Override
    protected void visitContinent(Continent continent) {
        System.out.println("Stuff");
    }

    @Override
    protected void visitPark(Park park) {
        System.out.println("Stuff");
    }
}
