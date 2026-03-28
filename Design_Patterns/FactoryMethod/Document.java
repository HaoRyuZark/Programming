
public abstract class Document {

    private String content;
     
    abstract void append(String content);

    abstract void find(String pattern);
}
