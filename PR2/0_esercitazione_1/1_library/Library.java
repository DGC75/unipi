public interface Library {
    

    public void remove(Book b) throws Exception;
    // Rimuove tutti i libri identici a b dalla libreria, lancia un'eccezione
    // se il libro non e' presente
    
    public void insert(Book b) throws Exception;
    // Inserisce il libro b nella libreria lancia una eccezione se la libreria e piena


    public String[] getAuthorByPublisher(String pub);
    // Restituisce l'elenco degli autori che hanno pubblicato per pub
    
    
}

