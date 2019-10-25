package visitor;

import syntaxtree.*;
import java.util.*;

class SymTab
{
   ErrorThrower police = new ErrorThrower();
   HashMap<String,ClassTab> cList;
   
   //0->outside any class
   //1->scope is curr_c
   //2->scope is curr_f
   int scope_flag;

   ClassTab curr_c;
   FunctionTab curr_f;   
 
   SymTab()
   {
      cList = new HashMap<String,ClassTab>();
      scope_flag=0;
      curr_c=null;
      curr_f=null;
   }

   boolean findClass(String cn)
   {
      return cList.containsKey(cn);
   }

   void insertClass(String cn)
   {
      ClassTab objc = new ClassTab(cn);
      if(!cList.containsKey(cn))
      {
         cList.put(cn,objc);
      }
      else
      {
         police.throwType("in insertClass(String)");
      }

   }
 
   void insertClass(String cn, String pt)
   {
      ClassTab objc = new ClassTab(cn,pt);
      if(!cList.containsKey(cn))
      {
         cList.put(cn,objc);
      }
      else
      {
         police.throwType("in insertClass(String,String)");
      }
   }
  
   void insertFunction(String fname,String rtype)
   {
      curr_c.insertFunction(fname, rtype);
   }

   void insertFnArgument(String type, String id)
   {
      curr_f.insertArgument(type, id);
   }

   void setCurrClass(String cn)
   {
      scope_flag=1;
      curr_c = cList.get(cn);
   }

   void setCurrFn(String cf)
   {
      scope_flag=2;
      curr_f = curr_c.fnList.get(cf);
   }

   void unsetCurrFn()
   {
      scope_flag=1;
      curr_f=null;
   }

   void unsetCurrClass()
   {
      scope_flag = 0;
      curr_c=null;
   }

   void insertField(String type,String id)
   {
      switch(scope_flag)
      {
         case 1:
            curr_c.insertCField(type, id);
         break;
         case 2:
            curr_f.insertFField(type, id);
         break;
         default:
            //Will never be encountered
      }
   }

   boolean checkAncestor(String child,String parent)
   {
      if(cList.get(child).classParent.equals(""))return false;
      else if(cList.get(child).classParent.equals(parent))return true;
      else return this.checkAncestor(cList.get(child).classParent, parent);
   }

   boolean verifySignature(String cname, String fname, ArrayList<String> signature)
   {
      ClassTab ct = cList.get(cname);
      if(ct.findFunction(fname))
      {
         if(ct.verifySignature(fname,signature,this))return true;
         else return false;
      }
      else
      {
         //if ct has no parent, then nothing
         //else search in the parent
         if(ct.classParent.equals(""))return false;
         else return this.verifySignature(ct.classParent, fname, signature);        
      }
   }

   //Only called if signature has been verified
   String getReturnType(String cname, String fname, ArrayList<String> signature)
   {
      ClassTab ct = cList.get(cname);
      if(ct.findFunction(fname))return ct.getReturnType(fname, signature);
      else return this.getReturnType(ct.classParent, fname, signature);
   }

   /**
    * Checks and returns if variable var is declared as a field in Class c or its superclass recursively.
    * @param c
    * @param var
    * @return boolean
    */
    boolean findVarInClass(ClassTab c, String var)
    {
      if(c.cfList.containsKey(var))return true;
      else
      {
         if(c.classParent.equals(""))return false;
         else return this.findVarInClass(this.cList.get(c.classParent),var);
      }
    }
   
    /**
    * Checks and returns whether the given variable can be legally scoped
    * @param var
    * @return boolean
    */
   boolean findVariable(String var)
   {
      //Search if the given variable is in the current scope
      return curr_f.argList.contains(var) || curr_f.ffList.containsKey(var) || this.findVarInClass(curr_c,var);
   }

   String getTypeInClass(ClassTab c, String var)
   {
      if(c.cfList.containsKey(var))return c.cfList.get(var);
      else return this.getTypeInClass(this.cList.get(c.classParent), var);
   }

   String getType(String var)
   {  
      //Invoked only if findVariable returns true
      if(curr_f.argList.contains(var))
      {
         return curr_f.getArgumentType(var);
      }
      else if(curr_f.ffList.containsKey(var))
      {
         return curr_f.ffList.get(var);
      }
      else
      {
         return this.getTypeInClass(curr_c,var);
      }
   }

   boolean inCycle(String p, String c)
   {
      if(cList.containsKey(p))
      {
         if(p.equals(c))return true;
         else return this.inCycle(cList.get(p).classParent,c);
      }
      else
      {
         if(p.equals(""))return false;
         else 
         {
            police.throwSymbol("::" + p + " not found");
            return false;
         }
      }
   }

   boolean hasInheritanceCycle()
   {
      boolean flag = false;
      Iterator it = cList.entrySet().iterator();
      while(it.hasNext())
      {
         Map.Entry elm = (Map.Entry)it.next();
         String cname = (String)elm.getKey();
         String pname = cList.get(cname).classParent;
         if(this.inCycle(pname,cname))
         {
            flag = true;
            break;
         }
      }
      return flag;
   }

}