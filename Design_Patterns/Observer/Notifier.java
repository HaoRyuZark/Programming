
public class Notifier {

    private List<User> users;

    public Notifier() {
        users = new ArrayList<>();
    }

    public void subscribe(User user) {
        this.users.add(user);
    }
    
    public void unsubscribe(User user) {
        this.users.remove(user);
    }

    public void notify() {
        users.forEach(u -> u.update);
    }
}
