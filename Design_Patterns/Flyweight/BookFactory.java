
public class BookFactory {

    private static vinal Map<String, BookFlyweight> bookFlyweights = new HashMap<>();

    public static BookFlyweight getBookFlyweight(String genre, String distributor) {

        if (bookFlyweights.get(genre) == null) {
            bookFlyweights.put(genre, new BookFlyweight(genre, distributor));
        }

        return bookFlyweights.get(genre);
    }
}
