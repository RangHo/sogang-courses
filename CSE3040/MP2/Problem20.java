import java.util.*;

import org.jsoup.*;
import org.jsoup.nodes.*;
import org.jsoup.parser.*;
import org.jsoup.select.*;

public class Problem20 {
    public static void main(String[] args) {
        ArrayList<BookInfo> books;
        books = BookReader.readBooksJsoup("https://www.barnesandnoble.com/b/books/_/N-1fZ29Z8q8");
        Collections.sort(books);
        for (int i = 0; i < books.size(); i++) {
            BookInfo book = books.get(i);
            System.out.println(book);
        }
    }
}

class BookInfo implements Comparable<BookInfo> {
    
    private int rank;

    private String title;

    private String author;

    private double price;

    public static class Builder {

        private int rank = -1;

        private String title = null;

        private String author = null;

        private double price = Double.NaN;

        public Builder rank(int value) {
            this.rank = value;
            return this;
        }

        public Builder title(String value) {
            this.title = value;
            return this;
        }

        public Builder author(String value) {
            this.author = value;
            return this;
        }

        public Builder price(double value) {
            this.price = value;
            return this;
        }

        public BookInfo build() {
            return new BookInfo(this);
        }

        public boolean isComplete() {
            return this.rank != -1
                   && this.title != null
                   && this.author != null
                   && this.price != Double.NaN;
        }
    }

    private BookInfo(Builder builder) {
        this.rank = builder.rank;
        this.title = builder.title;
        this.author = builder.author;
        this.price = builder.price;
    }

    @Override
    public int compareTo(BookInfo that) {
        return that.rank - this.rank;
    }

    @Override
    public String toString() {
        return String.format(
            "#%d %s, %s, $%.2f",
            this.rank, this.title, this.author, this.price
        );
    }
}

class BookReader {
    public static ArrayList<BookInfo> readBooksJsoup(String url) {
        ArrayList<BookInfo> books = new ArrayList<BookInfo>();

        try {
            Document document = Jsoup.connect(url).get();
            Elements products = document.select("ol.product-shelf-list.product-list-view > li");

            for (Element product : products)
                books.add(new BookInfo.Builder()
                    .rank(Integer.parseInt(product.select(".count").text()))
                    .title(product.select("h3.product-info-title > a").text())
                    .author(product.select(".product-shelf-author").text().substring(3))
                    .price(Double.parseDouble(product.select("span.current").text().substring(1)))
                    .build()
                );

        } catch (Exception e) {
            return null;
        }

        return books;
    }
}

