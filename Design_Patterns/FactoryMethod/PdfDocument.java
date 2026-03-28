public class PdfDocument extends Document {

    public PdfDocument(){}
    
    public PdfDocument(String content){
        this.content = content;
    }

    @Override
    public void append(String content) {
        System.out.println("Appending" + content + "\n");
    }

    @Override
    public void find(String pattern) {
        System.out.println("Finding" + pattern + "\n");
    }
}
