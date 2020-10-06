public class MyBook implements Book {

    String  author;
    String  title;
    String  publisher;
    int     publ_year;

    public MyBook(final String auth, final String titl, final String publ, final int year) {
        author = auth;
        title = titl;
        publisher = publ;
        publ_year = year;
    }

    public String getAuthor() {
        return this.author;
    }

    public String getTitle() {
        return this.title;
    }

    public String getPublisher() {
        return this.publisher;
    }

    public int getYear() {
        return publ_year;
    }

    public boolean sameAuthor(final Book b) {
        if (this.author.equals(b.getAuthor())) {
            return true;
        }

        return false;
    }

    public boolean sameTitle(final Book b) {
        if (this.title.equals(b.getTitle())) {
            return true;
        }

        return false;
    }

    public boolean samePublisher(final Book b) {
        if (this.publisher.equals(b.getPublisher())) {
            return true;
        }

        return false;
    }

    public boolean sameYear(final Book b) {
        if (b.getYear() == this.publ_year) {
            return true;
        }

        return false;
    }

    public boolean equals(final Book b) {
        
        if(!(sameAuthor(b)) || !(samePublisher(b)) || !(sameTitle(b)) || !(sameYear(b))){
            return false;
        }   


        return true;
    }    
}

