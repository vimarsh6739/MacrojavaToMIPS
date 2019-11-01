import syntaxtree.*;
import visitor.*;

public class P6 {
   public static void main(String [] args) {
      try {

         microIRParser mip = new microIRParser(System.in);
         Node root = microIRParser.Goal();
         root.accept(new MIPSGenerator<String>()); 
      }
      catch (ParseException e) {
         System.out.println(e.toString());
      }
   }
}