import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
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

public class Client {

    private Socket socket;

    private String username;

    private Scanner scanner;

    public Client(String address, int port) throws Exception {
        this.socket = new Socket(InetAddress.getByName(address), port);
        this.username = null;
    }

    public void send(byte[] content) {
        try {
            OutputStream out = this.socket.getOutputStream();
            out.write(content.length);
            out.write(content);
            out.flush();
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }

    public byte[] receive() {
        try {
            InputStream in = this.socket.getInputStream();
            
            int length = in.read();
            if (length < 0) {
                this.socket.close();
                throw new IOException("Connection was dropped.");
            }

            byte[] buffer = new byte[length];
            in.read(buffer);

            return buffer;
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(1);

            // This should be unreachable
            return null;
        }
    }

    public void authenticate() throws IOException {
        String id = input();
        while (!id.matches("[a-z0-9]+")) {
            System.out.println(
                "UserID must be a single word with lowercase alphabets and numbers."
            );
            id = input();
        }

        ClientPacket packet = new ClientPacket();
        packet.add("action", "authenticate");
        packet.add("username", id);
        send(packet.serialize());

        this.username = id;
    }

    public boolean process() throws IOException {
        String command = input();

        ClientPacket req = new ClientPacket();
        req.add("action", command);

        switch (command) {
            case "add":
                processAdd(req);
                return true;

            case "borrow":
                processBorrow(req);
                return true;

            case "return":
                processReturn(req);
                return true;

            case "info":
                processInfo(req);
                return true;

            case "search":
                processSearch(req);
                return true;

            case "exit":
                try {
                    this.socket.close();
                } catch (Exception e) {
                    // Do nothing
                }
                return false;

            default:
                processHelp();
                return true;
        }
    }

    public void processAdd(ClientPacket req) {
        String title = input("add-title");
        if (title.length() == 0)
            return;

        String author = input("add-author");
        if (author.length() == 0)
            return;

        // TODO: implement add command
        req.add("title", title);
        req.add("author", author);
        send(req.serialize());

        ClientPacket res = ClientPacket.from(receive());
        System.out.println(res.getProperty("message"));
    }

    public void processBorrow(ClientPacket req) {
        String title = input("borrow-title");
        if (title.length() == 0)
            return;

        // TODO: implement borrow command
        req.add("title", title);
        send(req.serialize());

        ClientPacket res = ClientPacket.from(receive());
        System.out.println(res.getProperty("message"));
    }

    public void processReturn(ClientPacket req) {
        String title = input("return-title");
        if (title.length() == 0)
            return;

        // TODO: implement return command
        req.add("title", title);
        send(req.serialize());

        ClientPacket res = ClientPacket.from(receive());
        System.out.println(res.getProperty("message"));
    }

    public void processInfo(ClientPacket req) {
        send(req.serialize());

        ClientPacket res = ClientPacket.from(receive());
        
        int count = Integer.parseInt(res.getProperty("count"));
        System.out.println("You are currently borrowing " + count + " books:");
        for (int i = 1; i <= count; i++) {
            BookInfo book
                = new BookInfo(new String(receive(), StandardCharsets.UTF_8));
            System.out.printf(
                "%d. %s, %s\n",
                i, book.title, book.author
            );
        }
    }

    public void processSearch(ClientPacket req) {
        String query = input("search-string");
        while (query.length() != 0) {
            if (query.length() > 2)
                break;

            System.out.println("Search string must be longer than 2 characters.");
            query = input("search-string");
        }

        // TODO: implement search command
        req.add("query", query);
        send(req.serialize());

        ClientPacket res = ClientPacket.from(receive());

        int count = Integer.parseInt(res.getProperty("count"));
        System.out.println("Your search matched " + count + " results.");
        for (int i = 1; i <= count; i++) {
            BookInfo book
                = new BookInfo(new String(receive(), StandardCharsets.UTF_8));
            System.out.printf(
                "%d. %s, %s\n",
                i, book.title, book.author
            );
        }
    }

    public void processHelp() {
        System.out.println("[available commands]");
        System.out.println("add: add a new book to the list of books.");
        System.out.println("borrow: borrow a book from the library.");
        System.out.println("return: return a book to the library.");
        System.out.println("info: show list of books I am currently borrowing.");
        System.out.println("search: search for books.");
    }

    public String input() {
        return input(
            (this.username == null) 
            ? "Enter UserID>"
            : this.username + ">"
        );
    }

    public String input(String prompt) {
        System.out.print(prompt + "> ");

        String result = this.scanner.nextLine();

        return result;
    }

    public void registerScanner(Scanner sc) {
        this.scanner = sc;
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Please give the IP address and port number as arguments.");
            System.exit(1);
        }

        Scanner sc = new Scanner(System.in);

        try {
            int port = Integer.parseInt(args[1]);
            Client client = new Client(args[0], port);

            client.registerScanner(sc);

            client.authenticate();

            while (client.process());
        } catch (Exception e) {
            System.err.println(e.getMessage());
            System.err.println("Connection establishment failed.");
            System.exit(2);
        }

        sc.close();
    }
}

class BookInfo{

    public final String title;

    public final String author;

    public final String borrower;

    public BookInfo(String info) {
        String[] splitted = info.split("\t");
        this.title = splitted[0];
        this.author = splitted[1];
        this.borrower = splitted[2];
    }
}

class ClientPacket {

    private Map<String, String> properties;

    public static ClientPacket from(byte[] xml) {
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

        ClientPacket packet = new ClientPacket();

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

    public ClientPacket() {
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

