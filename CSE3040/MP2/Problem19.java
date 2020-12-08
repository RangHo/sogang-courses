import java.io.*;
import java.net.*;
import java.util.*;

public class Problem19 {
    public static void main(String[] args) {
        ArrayList<BookInfo> books;
        books = BookReader.readBooks("https://www.barnesandnoble.com/b/books/_/N-1fZ29Z8q8");
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
    private static final String RANK_HEADER = "<div class=\"count\">";

    private static final String TITLE_HEADER = "<div class=\"product-shelf-title pr-m\"><h3 class=\"product-info-title\">";

    private static final String AUTHOR_HEADER = "<div class=\"product-shelf-author contributors\">by ";

    private static final String PRICE_HEADER = "<span class=\"current\">";

    public static ArrayList<BookInfo> readBooks(String url) {
        ArrayList<BookInfo> books = new ArrayList<>();

        try {
            URL src = new URL(url);
            BufferedReader reader = new BufferedReader(
                new InputStreamReader(src.openStream())
            );

            String document = "";
            BookInfo.Builder bookBuilder = new BookInfo.Builder();
            StringBuilder sb = new StringBuilder();

            String line = null;
            while ((line = reader.readLine()) != null)
                sb.append(line);

            document = sb.toString();
            sb = new StringBuilder();

            while (true) {
                if (document.indexOf(RANK_HEADER) == -1)
                    break;

                // Parse the rank information
                document = document.substring(
                    document.indexOf(RANK_HEADER) + RANK_HEADER.length()
                );
                int i = 0;
                while (document.charAt(i) != '<')
                    sb.append(document.charAt(i++));

                bookBuilder.rank(Integer.parseInt(sb.toString()));
                sb = new StringBuilder();

                // Parse the title information
                document = document.substring(
                    document.indexOf(TITLE_HEADER) + TITLE_HEADER.length()
                );

                document = document.substring(
                    document.indexOf('>') + 1
                );

                i = 0;
                while (document.charAt(i) != '<')
                    sb.append(document.charAt(i++));

                bookBuilder.title(sb.toString());
                sb = new StringBuilder();

                // Parse the author information
                document = document.substring(
                    document.indexOf(AUTHOR_HEADER) + AUTHOR_HEADER.length()
                );

                // There may be multiple authors
                while (true) {
                    document = document.substring(
                        document.indexOf('>') + 1
                    );

                    i = 0;
                    while (document.charAt(i) != '<')
                        sb.append(document.charAt(i++));

                    document = document.substring(
                        document.indexOf("</a>") + 4
                    );

                    if (!document.startsWith(","))
                        break;
                    else
                        sb.append(",");
                }

                bookBuilder.author(sb.toString().replaceAll("^ +| +$|( )+", "$1"));
                sb = new StringBuilder();

                // Parse the price information
                document = document.substring(
                    document.indexOf(PRICE_HEADER) + PRICE_HEADER.length()
                );

                document = document.substring(
                    document.indexOf('$') + 1
                );

                i = 0;
                while (document.charAt(i) != '<')
                    sb.append(document.charAt(i++));

                bookBuilder.price(Double.parseDouble(sb.toString()));
                sb = new StringBuilder();

                books.add(bookBuilder.build());
                bookBuilder = new BookInfo.Builder();
            }
        } catch (Exception e) {
            System.out.println(e);
        }

        return books;
    }
        
}

