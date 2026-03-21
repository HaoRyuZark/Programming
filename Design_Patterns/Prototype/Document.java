
public class Document implements DocumentPrototype{

    private String content;
    private String name; 

    @Override
    public Document cloneDocument() {
        return new Document(content, name);
    }
}
