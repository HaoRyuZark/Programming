
public abstract class GameLoader {
    
    /**
     * Template method with all substeps open for modification inside all of the other 
     * subclasses
     * */
    public abstract void loadGame() {
        byte[] data = loadLocalData();
        loadGraphics();
        loadMaps();
        loadNetworkConfig();

    }

    public abstract byte[] loadLocalData();
    
    public abstract void loadGraphics();

    public abstract void loadMaps();
    
    public abstract void loadNetworkConfig();
}

