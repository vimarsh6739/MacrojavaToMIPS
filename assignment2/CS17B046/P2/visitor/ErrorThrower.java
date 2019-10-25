package visitor;

import syntaxtree.*;
import java.util.*;

class ErrorThrower
{
   ErrorThrower()
   {}

   void throwType(String m)
   {
      System.out.println("Type error");
      System.exit(0);
   }

   void throwSymbol(String m)
   {
      System.out.println("Symbol not found");
      System.exit(0);
   }

}
