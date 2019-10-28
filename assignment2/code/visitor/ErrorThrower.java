package visitor;

import syntaxtree.*;
import java.util.*;

public class ErrorThrower
{
   ErrorThrower()
   {}

   public void throwType(String m)
   {
      System.out.println("Type error");
      System.exit(0);
   }

   public void throwSymbol(String m)
   {
      System.out.println("Symbol not found");
      System.exit(0);
   }

}
