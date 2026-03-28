
public class MinecraftLoader extends GameLoader {
    
    @Overrride
    public void loadGame() {
        byte[] data = loadLocalData();
        loadGraphics();
        loadMaps();
        loadNetworkConfig();

    }

    @Overrride
    public byte[] loadLocalData(){
        System.out.println("Stuff");
    }
    
    @Overrride
    public void loadGraphics(){ 
        System.out.println("Stuff");
    }

    @Overrride
    public void loadMaps(){ 
        System.out.println("Stuff");
    }
    
    @Overrride
    public void loadNetworkConfig(){ 
        System.out.println("Stuff");
    }
}
