import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

/**
 * Represents a server instance.
 */
public class Server {

    private ServerSocket server;

    private Database database;

    class Connection {

        private Socket socket;

        private String username;

        public Connection(Socket socket) {
            this.socket = socket;
        }

        public void send(byte[] content) throws IOException {
            OutputStream out = this.socket.getOutputStream();
            out.write(content.length);
            out.write(content);
            out.flush();
        }

        public byte[] receive() throws IOException {
            InputStream in = this.socket.getInputStream();
            
            int length = in.read();
            if (length < 0) {
                this.socket.close();
                throw new IOException("Connection was dropped.");
            }

            byte[] buffer = new byte[length];
            in.read(buffer);

            return buffer;
        }

        public void authenticate() throws Exception {
            ServerPacket packet = ServerPacket.from(receive());

            if (!packet.getProperty("action").equals("authenticate"))
                throw new Exception("This connection is not authenticated.");

            this.username = packet.getProperty("username");
        }

        public void dispatch(ServerPacket packet) throws IOException {
            String action = packet.getProperty("action");

            switch (action) {
                case "add":
                    addAction(packet);
                    return;

                case "borrow":
                    borrowAction(packet);
                    return;

                case "return":
                    returnAction(packet);
                    return;

                case "info":
                    infoAction(packet);
                    return;

                case "search":
                    searchAction(packet);
                    return;
            }
        }

        public void addAction(ServerPacket packet) throws IOException {
            String title = packet.getProperty("title");
            String author = packet.getProperty("author");

            ServerPacket res;
            if (database.addBook(title, author))
                res = ServerPacket.response(true, "A new book added to the list.");
            else
                res = ServerPacket.response(false, "The book already exists in the list.");

            send(res.serialize());
        }

        public void borrowAction(ServerPacket packet) throws IOException {
            String title = packet.getProperty("title");

            ServerPacket res;
            if (database.borrowBook(title, this.username))
                res = ServerPacket.response(true, "You borrowed a book. – " + title);
            else
                res = ServerPacket.response(false, "The book is not available.");

            send(res.serialize());
        }

        public void returnAction(ServerPacket packet) throws IOException {
            String title = packet.getProperty("title");

            ServerPacket res;
            if (database.returnBook(title, this.username))
                res = ServerPacket.response(true, "You returned a book. – " + title);
            else
                res = ServerPacket.response(false, "You did not borrow the book.");

            send(res.serialize());
        }

        public void infoAction(ServerPacket packet) throws IOException {
            List<Book> borrowed = new ArrayList<>();

            for (Book item : database.getBooks())
                if (this.username.equals(item.getBorrower()))
                    borrowed.add(item);

            ServerPacket res = new ServerPacket();
            res.add("status", "success");
            res.add("count", Integer.toString(borrowed.size()));
            send(res.serialize());

            for (Book item : borrowed)
                send(item.toString().getBytes(StandardCharsets.UTF_8));
        }

        public void searchAction(ServerPacket packet) throws IOException {
            Book[] results = database.searchBooks(packet.getProperty("query"));

            ServerPacket res = new ServerPacket();
            res.add("status", "success");
            res.add("count", Integer.toString(results.length));
            send(res.serialize());

            for (Book item : results)
                send(item.toString().getBytes(StandardCharsets.UTF_8));
        }
    }

    /**
     * Creates a server socket with the given port.
     *
     * @param port Port number to listen on.
     */
    public Server(int port) {
        try {
            this.server = new ServerSocket(port);
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.database = new Database("books.txt");
    }

    /**
     * Starts accepting connections from clients.
     */
    public void serve() {
        while (true) {
            try {
                Socket clientSocket = this.server.accept();
                Connection connection = new Connection(clientSocket);

                new Thread(() -> {
                    try {
                        connection.authenticate();

                        while (true) {
                            ServerPacket request
                                = ServerPacket.from(connection.receive());
                            connection.dispatch(request);
                        }
                    } catch (IOException e) {
                        System.err.println("Client disconnected.");
                    } catch (Exception e) {
                        System.err.println(e.getMessage());
                    }
                }).start();
            } catch (IOException e) {
                // Do nothing
            }
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Please give the port number as an argument.");
            System.exit(1);
        }

        int port = Integer.parseInt(args[0]);

        Server server = new Server(port);
        server.serve();
    }
}

/**
 * Represents a database of books and their statuses.
 */
class Database {

    private String filename;

    private List<Book> books;

    /**
     * Creates a new database of book from a file.
     *
     * @param filename Name of the file to read the initial data.
     */
    public Database(String filename) {
        this.filename = filename;
        this.books = new ArrayList<Book>();
        
        try {
            Scanner sc = new Scanner(new File(filename));
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                String[] splitted = line.split("\t");

                books.add(new Book(splitted[0], splitted[1], splitted[2]));
            }
        } catch (FileNotFoundException e) {
            System.err.println("File is not found!");
        }
    }

    public List<Book> getBooks() { return this.books; }

    /**
     * Synchronizes the text file with the list of books in memory.
     */
    public synchronized void synchronize() {
        try {
            PrintWriter writer = new PrintWriter(new FileWriter(this.filename));
            for (Book item : this.books)
                writer.printf(
                    "%s\t%s\t%s\n",
                    item.getTitle(),
                    item.getAuthor(),
                    (item.getBorrower() == null) ? "-" : item.getBorrower()
                );

            writer.close();
        } catch (IOException e) {
            // Do nothing
        }
    }

    /**
     * Adds a new book to the database.
     *
     * @param title Title of the book.
     * @param author Author of the book.
     */
    public boolean addBook(String title, String author) {
        // Check if the book with same name exists
        for (Book item : this.books)
            if (item.getTitle().equals(title))
                return false;

        Book entry = new Book(title, author, null);
        this.books.add(entry);
        this.books.sort(null);

        synchronize();

        return true;
    }

    /**
     * Borrows a book from the database.
     *
     * @param title Title of the book to borrow.
     * @param username User to borrow the book.
     */
    public boolean borrowBook(String title, String username) {
        // Check if the book with same name exists
        for (Book item : this.books) {
            if (item.getTitle().equalsIgnoreCase(title)) {
                if (item.getBorrower() != null)
                    return false;

                item.setBorrower(username);
                synchronize();

                return true;
            }
        }

        return false;
    }

    /**
     * Returns a book to the database.
     *
     * @param title Title of the book to return.
     * @param username User who returns the book.
     */
    public boolean returnBook(String title, String username) {

        // Check if the book with same name exists
        for (Book item : this.books) {
            if (item.getTitle().equalsIgnoreCase(title)) {
                if (!username.equals(item.getBorrower()))
                    return false;

                item.setBorrower(null);

                synchronize();
                return true;
            }
        }

        return false;
    }

    /**
     * Searches for books in the database.
     *
     * @param query Title of the book to search for.
     */
    public Book[] searchBooks(String query) {
        List<Book> matches = new ArrayList<>();
        for (Book item : this.books)
            if (item.getTitle().toLowerCase().contains(query)
                || item.getAuthor().toLowerCase().contains(query))
                matches.add(item);

        Book[] result = {};
        return matches.toArray(result);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Book item : this.books) {
            sb.append('[');
            sb.append(item.getTitle());
            sb.append(',');
            sb.append(item.getAuthor());
            if (item.getBorrower() != null) {
                sb.append(',');
                sb.append(item.getBorrower());
            }
            sb.append(']');
        }
        return sb.toString();
    }
}

class Book implements Comparable<Book> {

    private String title;

    private String author;

    private String borrower;

    public Book(String title, String author, String borrower) {
        this.title = title;
        this.author = author;
        this.borrower = borrower;
    }

    public String getTitle() { return this.title; }

    public String getAuthor() { return this.author; }

    public String getBorrower() { return this.borrower; }

    public void setBorrower(String username) { this.borrower = username; }

    @Override
    public int compareTo(Book that) {
        return this.title.compareToIgnoreCase(that.title);
    }

    @Override
    public String toString() {
        return this.title + "\t"
               + this.author + "\t"
               + ((this.borrower != null) ? this.borrower : "-");
    }
}

class ServerPacket {

    private Map<String, String> properties;

    public static ServerPacket from(byte[] xml) {
        Document document = null;
        try {
            document = DocumentBuilderFactory
                       .newInstance()
                       .newDocumentBuilder()
                       .parse(new ByteArrayInputStream(xml));
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }

        ServerPacket packet = new ServerPacket();

        document.getDocumentElement().normalize();
        NodeList props = document.getDocumentElement().getChildNodes();
        for (int i = 0; i < props.getLength(); i++) {
            Node prop = props.item(i);
            if (prop.getNodeType() != Node.ELEMENT_NODE)
                continue;

            Element propElement = (Element)prop;
            packet.add(propElement.getTagName(), propElement.getTextContent());
        }
        
        return packet;
    }

    public static ServerPacket response(boolean success, String message) {
        ServerPacket packet = new ServerPacket();
        if (success)
            packet.add("status", "success");
        else
            packet.add("status", "error");
        packet.add("message", message);

        return packet;
    }

    public ServerPacket() {
        this.properties = new HashMap<>();
    }

    public void add(String property, String value) {
        this.properties.put(property, value);
    }

    public byte[] serialize() {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.newDocument();

            Element packet = document.createElement("packet");
            document.appendChild(packet);

            for (Map.Entry<String, String> entry : this.properties.entrySet()) {
                Element key = document.createElement(entry.getKey());
                key.appendChild(document.createTextNode(entry.getValue()));
                packet.appendChild(key);
            }

            Transformer transformer = TransformerFactory
                                      .newInstance()
                                      .newTransformer();
            transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");

            ByteArrayOutputStream output = new ByteArrayOutputStream();
            transformer.transform(
                new DOMSource(document),
                new StreamResult(output)
            );
            return output.toByteArray();

        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public String getProperty(String prop) {
        return this.properties.get(prop);
    }
}

