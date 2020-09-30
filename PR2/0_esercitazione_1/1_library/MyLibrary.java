import java.util.ArrayList;

public class MyLibrary implements Library {

    Book[] arr_books;
    int dim;

    public MyLibrary(int size){
        dim = size;
        arr_books = new Book[size];
    }

    public void remove( Book b) throws Exception {
        Boolean removed = false;

        for(int i = 0; i < dim; i++){
            if(b.equals(arr_books[i])){
                arr_books[i] = null;
                removed = true;
            }
        }

        if(removed == false){
            throw new Exception();
        }

    }
    // Rimuove tutti i libri identici a b dalla libreria, lancia un'eccezione
    // se il libro non e' presente

    public void insert(Book b) throws Exception {
        
        Boolean inserted = false;
        int i = 0;

        while(inserted== false && i < this.dim){
            if(this.arr_books[i] == null){
                this.arr_books[i] = b;
                inserted = true;
            }
            i+=1;
        }

        if(inserted == false){
            throw new Exception();
        }
        this.dim++;
    }
    // Inserisce il libro b nella libreria lancia una eccezione se la libreria e
    // piena

    public String[] getAuthorByPublisher( String pub) {

        ArrayList<String> list = new ArrayList<String>();

        for(int i = 0; i < this.dim; i++){
            if(this.arr_books[i] != null && this.arr_books[i].getPublisher().equals(pub)){
                list.add(this.arr_books[i].getAuthor());
            }
        }

        return list.toArray(new String[0]);
    }
    // Restituisce l'elenco degli autori che hanno pubblicato per pub
     
}
