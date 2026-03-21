

public class MySingleton {
   
    /*
     * It is important to make it volatile to prevent partially initalized objects 
     * */
    public static volatile MySingleton instance = null;

    private int secretCode; 

    private MySingleton() {}

    private MySingleton(int secretCode) {
        this.secretCode = secretCode;
    }

    /*
     * To make our singleton thread safe we use a synchronized block, and to not waste performance we make sure
     * that it only gets synchronized for the case that the instance is really null. But it can not be cached.
     * */
    public static MySingleton getInstance() {
    
        /*
         * The local variable allows us to get extra performance by already storing the instance 
         * in the memory instead of fetching it two times from the main memory
         * */
        MySingleton result = instance;

        if (result == null) {
        
            synchronized (MySingleton.class) {
                result = instance; 
                if (result == null) {

                    instance = result = MySingleton();
                }
            }
        }
       
        return result;
    }


    public static MySingleton getInstance(int secretCode) {
    
        MySingleton result = instance;

        if (result == null) {
        
            synchronized (MySingleton.class) {
                result = instance; 
                if (result == null) {

                    instance = result = MySingleton(secretCode);
                }
            }
        }
       
        return result;
    }

    public int getSecretCode() { return this.secretCode; }

    public void setSecretCode(int secretCode) { this.secretCode = secretCode; }
}
