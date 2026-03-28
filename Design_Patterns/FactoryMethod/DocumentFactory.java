
public class DocumentFactory {

    public static Document getDocument(String content, DocType type) {
 
        switch (type) {
            PDF -> return new PdfDocument(content); 
            TEXT -> return new TextDocument(content); 
            DOCX -> return new DocxDocuement(content);
            _ -> throw new Exception("No such document type");
        }
    }
}
