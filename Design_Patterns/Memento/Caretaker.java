
public class Caretaker {

  private ArrayList<Memento> mementi;

  public Caretaker() {
    this.mementi = new ArrayList<>();
  }
  
  public void addMemento(Memento m) {
    this.mementi.add(m);
  }

  public Memento getMemento(int index) {
    return this.mementi.get(index);
  }
}


