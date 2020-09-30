import java.util.Scanner;

public class Benvenuto {
    private static Scanner input = new Scanner(System.in);

    public static void main(String[ ] args) {
         System.out.println("Come ti chiami?");
         String name = input.nextLine( );
         System.out.println("Ciao " + name + "!!");
     }
}