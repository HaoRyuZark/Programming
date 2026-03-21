
public class TextEditor {

  private StringBuilder text;
  
  public TextEditor() {
    this.text = new StringBuilder();
  }

  public void append(String text) {
    text.append(text);
  }

  public String getContent() {
    return this.text.toString();
  }

  public Memento save() {
    return new Memento(text.toString());
  }

  public void restore(Memento memento) {
    text = new StringBuilder(memento.getState());
  }
}
