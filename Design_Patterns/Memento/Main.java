
public class Main {

  public static void main(String[] args) {

    TextEditor textEditor = new TextEditor();
    Caretaker caretaker = new Caretaker();

    textEditor.append("Hello");
    caretaker.addMemento(textEditor.save());

    textEditor.append("World");
    caretaker.addMemento(textEditor.save());

    textEditor.restore(caretaker.getMemento(0));
    
    textEditor.restore(caretaker.getMemento(1));
  }
}
