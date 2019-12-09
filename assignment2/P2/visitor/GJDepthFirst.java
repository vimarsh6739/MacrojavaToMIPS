//
// Generated by JTB 1.3.2
//

package visitor;

import syntaxtree.*;
import java.util.*;

/**
 * Provides default methods which visit each node in the tree in depth-first
 * order.  Your visitors may extend this class.
 */

public class GJDepthFirst<R,A> implements GJVisitor<R,A> {

   //initialize the symbol table and error thrower
   SymTab T = new SymTab();
   ErrorThrower police = new ErrorThrower();
   //
   // Auto class visitors--probably don't need to be overridden.
   //
   public R visit(NodeList n, A argu) {
      R _ret=null;
      int _count=0;
      for ( Enumeration<Node> e = n.elements(); e.hasMoreElements(); ) {
         e.nextElement().accept(this,argu);
         _count++;
      }
      return _ret;
   }

   public R visit(NodeListOptional n, A argu) {
      if ( n.present() ) {
         R _ret=null;
         int _count=0;
         for ( Enumeration<Node> e = n.elements(); e.hasMoreElements(); ) {
            e.nextElement().accept(this,argu);
            _count++;
         }
         return _ret;
      }
      else
         return null;
   }

   public R visit(NodeOptional n, A argu) {
      if ( n.present() )
         return n.node.accept(this,argu);
      else
         return null;
   }

   public R visit(NodeSequence n, A argu) {
      R _ret=null;
      int _count=0;
      for ( Enumeration<Node> e = n.elements(); e.hasMoreElements(); ) {
         e.nextElement().accept(this,argu);
         _count++;
      }
      return _ret;
   }

   //Return the name of the identifier
   public R visit(NodeToken n, A argu) { return (R)n.tokenImage; }

   //
   // User-generated visitor methods below
   //
   
   /**
    * f0 -> MainClass()
    * f1 -> ( TypeDeclaration() )*
    * f2 -> <EOF>
    */

   public R visit(Goal n, A argu) {
      R _ret=null;
      //Build symbol table
      n.f0.accept(this, (A)"one");
      n.f1.accept(this, (A)"one");
      n.f2.accept(this, (A)"one");
      
      //Check for a inheritance Cycle
      if(T.hasInheritanceCycle())police.throwType(" Inheritance Cycle detected");

      //Do type checking
      n.f0.accept(this,(A)"two");
      n.f1.accept(this, (A)"two");
      n.f2.accept(this, (A)"two");

      //Program type checked
      System.out.println("Program type checked successfully");
      return _ret;
   }

   /**
    * f0 -> "class"
    * f1 -> Identifier()
    * f2 -> "{"
    * f3 -> "public"
    * f4 -> "static"
    * f5 -> "void"
    * f6 -> "main"
    * f7 -> "("
    * f8 -> "String"
    * f9 -> "["
    * f10 -> "]"
    * f11 -> Identifier()
    * f12 -> ")"
    * f13 -> "{"
    * f14 -> PrintStatement()
    * f15 -> "}"
    * f16 -> "}"
    */
   public R visit(MainClass n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);
      n.f7.accept(this, argu);
      n.f8.accept(this, argu);
      n.f9.accept(this, argu);
      n.f10.accept(this, argu);
      n.f11.accept(this, argu);
      n.f12.accept(this, argu);
      n.f13.accept(this, argu);
      n.f14.accept(this, argu);
      n.f15.accept(this, argu);
      n.f16.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> ClassDeclaration()
    *       | ClassExtendsDeclaration()
    */
   public R visit(TypeDeclaration n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "class"
    * f1 -> Identifier()
    * f2 -> "{"
    * f3 -> ( VarDeclaration() )*
    * f4 -> ( MethodDeclaration() )*
    * f5 -> "}"
    */
   public R visit(ClassDeclaration n, A argu) {
      R _ret=null;
      String cn = "";
      n.f0.accept(this, argu);
      cn = (String)n.f1.accept(this, argu);
      if(((String)argu).equals("one"))
      {
         //Insert class into the table
         T.insertClass(cn);
      }
      
      //Set the current context to class before accepting variables
      T.setCurrClass(cn);
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      n.f5.accept(this, argu);
      T.unsetCurrClass();
      return _ret;
   }

   /**
    * f0 -> "class"
    * f1 -> Identifier()
    * f2 -> "extends"
    * f3 -> Identifier()
    * f4 -> "{"
    * f5 -> ( VarDeclaration() )*
    * f6 -> ( MethodDeclaration() )*
    * f7 -> "}"
    */
   public R visit(ClassExtendsDeclaration n, A argu) {
      R _ret=null;
      String cn = "";
      String pt = "";
      n.f0.accept(this, argu);
      cn = (String)n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      pt = (String)n.f3.accept(this, argu);
      if(((String)argu).equals("one"))
      {
         //Insert class and superclass entry into the table
         T.insertClass(cn,pt);
      }
      if(((String)argu).equals("two"))
      {
         //Check if superclass is valid
         if(!T.findClass(pt))
         {
            police.throwSymbol("::"+pt);
         }
      }
      n.f4.accept(this, argu);
      //Set the scope
      T.setCurrClass(cn);
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);
      n.f7.accept(this, argu);
      T.unsetCurrClass();
      return _ret;
   }

   /**
    * f0 -> Type()
    * f1 -> Identifier()
    * f2 -> ";"
    */
   public R visit(VarDeclaration n, A argu) {
      R _ret=null;
      String typ="";
      String id= "";
      typ = (String)n.f0.accept(this, argu);
      id = (String)n.f1.accept(this, argu);
      if(((String)argu).equals("one"))
      {
         T.insertField(typ,id);
      }
      if(argu.toString().equals("two"))
      {
         if(!typ.equals("int") && !typ.equals("int[]") && !typ.equals("boolean"))
         {
            if(!T.findClass(typ))police.throwSymbol(" in VarDeclaration of function");
         }
      }
      n.f2.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "public"
    * f1 -> Type()
    * f2 -> Identifier()
    * f3 -> "("
    * f4 -> ( FormalParameterList() )?
    * f5 -> ")"
    * f6 -> "{"
    * f7 -> ( VarDeclaration() )*
    * f8 -> ( Statement() )*
    * f9 -> "return"
    * f10 -> Expression()
    * f11 -> ";"
    * f12 -> "}"
    */
   public R visit(MethodDeclaration n, A argu) {
      R _ret=null;
      String rtype;
      String fname;
      String ret2 = "";
      n.f0.accept(this, argu);
      rtype = (String)n.f1.accept(this, argu);
      fname = (String)n.f2.accept(this, argu);
      
      if(((String)argu).equals("one"))
      {
         T.insertFunction(fname,rtype);
      }

      T.setCurrFn(fname);
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);

      //Accept the fn local variables and the statements
      n.f7.accept(this, argu);
      n.f8.accept(this, argu);
      n.f9.accept(this, argu);
      
      ret2 = (String)n.f10.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret2.equals(rtype))
         {
            if(ret2.equals("int") || ret2.equals("int[]") || ret2.equals("boolean"))
               police.throwType(" invalid return type in MethodDeclaration" + ret2);
            else
            {
               //ret2 is of type class and type is of type class
               //check if rtype is an ancestor of ret2
               if (!T.checkAncestor(ret2,rtype))
               {
                  police.throwType(" invalid return type in MethodDeclaration" + ret2);
               }
               else
               {;}
            }
         }
      }
      n.f11.accept(this, argu);
      n.f12.accept(this, argu);
      //Remove the current function from the scope 
      T.unsetCurrFn();

      return _ret;
   }

   /**
    * f0 -> FormalParameter()
    * f1 -> ( FormalParameterRest() )*
    */
   public R visit(FormalParameterList n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> Type()
    * f1 -> Identifier()
    */
   public R visit(FormalParameter n, A argu) {
      R _ret=null;
      String type = "";
      String id = "";
      type = (String)n.f0.accept(this, argu);
      id = (String)n.f1.accept(this, argu);
      
      if(((String)argu).equals("one"))
      {
         T.insertFnArgument(type,id);
      }

      if(((String)argu).equals("two"))
      {
         if(!type.equals("int") && !type.equals("int[]") && !type.equals("boolean"))
         {
            if(!T.findClass(type))police.throwSymbol(" in FormalParameter of function");
         }
      }
      return _ret;
   }

   /**
    * f0 -> ","
    * f1 -> FormalParameter()
    */
   public R visit(FormalParameterRest n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> ArrayType()
    *       | BooleanType()
    *       | IntegerType()
    *       | Identifier()
    */
   public R visit(Type n, A argu) {
      R _ret=null;
      String id;
      id = (String)n.f0.accept(this, argu);
      if(argu.toString().equals("two"))
      {
         //Using NodeChoice variable for use
         if(n.f0.which==3)
         {
            //Check if the type is a valid class
            if(!T.findClass(id))police.throwSymbol("::unknown type for "+ id);
         }
      }
      _ret = (R)id;
      return _ret;
   }

   /**
    * f0 -> "int"
    * f1 -> "["
    * f2 -> "]"
    */
   public R visit(ArrayType n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      _ret = (R)("int[]");
      return _ret;
   }

   /**
    * f0 -> "boolean"
    */
   public R visit(BooleanType n, A argu) {
      R _ret=null;
      _ret = (R)n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "int"
    */
   public R visit(IntegerType n, A argu) {
      R _ret=null;
      _ret = (R)n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> Block()
    *       | AssignmentStatement()
    *       | ArrayAssignmentStatement()
    *       | IfStatement()
    *       | WhileStatement()
    *       | PrintStatement()
    */
   public R visit(Statement n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "{"
    * f1 -> ( Statement() )*
    * f2 -> "}"
    */
   public R visit(Block n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> Identifier()
    * f1 -> "="
    * f2 -> Expression()
    * f3 -> ";"
    */
   public R visit(AssignmentStatement n, A argu) {
      R _ret=null;
      String id = "";
      String type = "";
      String ret = "";
      id = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret = (String)n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      if(argu.toString().equals("two"))
      {
         if(!T.findVariable(id))
         {
            police.throwSymbol(" in AssignmentStatement" + id);
         }

         type = T.getType(id);
         if(ret.equals("this"))ret=T.curr_c.className;

         if(!type.equals(ret))
         {

            if(type.equals("int") || type.equals("int[]") || type.equals("boolean"))
            {
               police.throwType(" in AssignmentStatement primitive");
            }
            else if (!T.checkAncestor(ret,type))
            {
               police.throwType(" in AssignmentStatement ");
            }
            else {;}
         }
      }
      return _ret;
   }

   /**
    * f0 -> Identifier()
    * f1 -> "["
    * f2 -> Expression()
    * f3 -> "]"
    * f4 -> "="
    * f5 -> Expression()
    * f6 -> ";"
    */
   public R visit(ArrayAssignmentStatement n, A argu) {
      R _ret=null;
      String id1,ret1,ret2;
      ret1 = "";ret2 = "";id1 = "";
      id1 = (String)n.f0.accept(this, argu);
      //Must be of type int-search in scopes
      if(argu.toString().equals("two"))
      {
         //Symbol not found
         if(!T.findVariable(id1))police.throwSymbol(" in ArrayAssignmentStatement");
         
         //id1 is found
         String type = T.getType(id1);
         if(!type.equals("int[]"))police.throwType(" in ArrayAssignmentStatement");
      }
      n.f1.accept(this, argu);
      ret1 = (String)n.f2.accept(this, argu);
      if(argu.toString().equals("two"))
      {
         if(!ret1.equals("int"))police.throwType(" in ArrayAssignmentStatement indexing");
      }

      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      ret2 = (String)n.f5.accept(this, argu);
      if(argu.toString().equals("two"))
      {
         if(!ret2.equals("int"))police.throwType(" In ArrayAssignmentStatement value");
      }
      n.f6.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> IfthenElseStatement()
    *       | IfthenStatement()
    */
   public R visit(IfStatement n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "if"
    * f1 -> "("
    * f2 -> Expression()
    * f3 -> ")"
    * f4 -> Statement()
    */
   public R visit(IfthenStatement n, A argu) {
      R _ret=null;
      String chk = "";
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      //check if the return type of f2 is boolean
      chk = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!chk.equals("boolean"))
         {
            police.throwType(" in IfThenStatement");
         }
      }
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "if"
    * f1 -> "("
    * f2 -> Expression()
    * f3 -> ")"
    * f4 -> Statement()
    * f5 -> "else"
    * f6 -> Statement()
    */
   public R visit(IfthenElseStatement n, A argu) {
      R _ret=null;
      String chk = "";
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      //check if the return type of f2 is boolean
      chk = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!chk.equals("boolean"))
         {
            police.throwType(" ifThenElseStmt");
         }
      }
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      n.f5.accept(this, argu);
      n.f6.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "while"
    * f1 -> "("
    * f2 -> Expression()
    * f3 -> ")"
    * f4 -> Statement()
    */
   public R visit(WhileStatement n, A argu) {
      R _ret=null;
      String chk = "";
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      //check if the return type of f2 is boolean
      chk = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!chk.equals("boolean"))
         {
            police.throwType(" While Statement");
         }
      }
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "System.out.println"
    * f1 -> "("
    * f2 -> Expression()
    * f3 -> ")"
    * f4 -> ";"
    */
   public R visit(PrintStatement n, A argu) {
      R _ret=null;
      String chk = "";
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      //check if the return type of f2 is integer
      chk = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!chk.equals("int"))
         {
            police.throwType(" in PrintStatement");
         }
      }
      n.f3.accept(this, argu);
      n.f4.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> OrExpression()
    *       | AndExpression()
    *       | CompareExpression()
    *       | neqExpression()
    *       | PlusExpression()
    *       | MinusExpression()
    *       | TimesExpression()
    *       | DivExpression()
    *       | ArrayLookup()
    *       | ArrayLength()
    *       | MessageSend()
    *       | PrimaryExpression()
    */
   public R visit(Expression n, A argu) {
      R _ret=null;
      _ret = n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "&&"
    * f2 -> PrimaryExpression()
    */
   public R visit(AndExpression n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         
         if(!ret1.equals("boolean") || !ret2.equals("boolean"))
         {
            police.throwType(" in AndExpression");
         }
         _ret = (R)("boolean");
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "||"
    * f2 -> PrimaryExpression()
    */
   public R visit(OrExpression n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals("boolean") || !ret2.equals("boolean"))
         {
            police.throwType(" in OrExpression");
         }
         _ret = (R)("boolean");
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "<="
    * f2 -> PrimaryExpression()
    */
   public R visit(CompareExpression n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals("int") || !ret2.equals("int"))
         {
            police.throwType(" in CompareExpression");
         }
         _ret = (R)("boolean");
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "!="
    * f2 -> PrimaryExpression()
    */
   public R visit(neqExpression n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals(ret2))
         {
            //If any are primitive(int,bool or int []) then throw error and exit
            if(ret1.equals("int")||ret1.equals("boolean")||ret1.equals("int[]"))
               police.throwType(" unmatched type in NeqExpression for ret1");
            
            if(ret2.equals("int")||ret2.equals("boolean")||ret2.equals("int[]"))
               police.throwType(" unmatched type in NeqExpression for ret2");
            
            //Both are non primitive
            //Check if the class is found in symbol table for both ret1 and ret2
            //if not then type error
            if(!T.findClass(ret1))
               police.throwType(" in NeqExpression::no class named "+ ret1);
            
            if(!T.findClass(ret2))
               police.throwType(" in NeqExpression::no class named "+ ret2);              
            
            //Both are present- check if ret1 is a superclass of ret2 or vice-versa
            if(!((T.checkAncestor(ret1,ret2))||(T.checkAncestor(ret2,ret1))))
               police.throwType(" in NeqExpression:: comparing unrelated types");

         }
         else
         {
            //Check if both the types are valid 
            if(ret1.equals("int")||ret1.equals("boolean")||ret1.equals("int[]"));
            else
            {
               //Check if non primitive is a member of symbol table T- if not, then 
               //its a type error(symbol not found only for undeclared vars)
               if(!T.findClass(ret1))
               police.throwType(" in NeqExpression::no class named "+ ret1);
            }
            
         }

         _ret = (R)"boolean";
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "+"
    * f2 -> PrimaryExpression()
    */
   public R visit(PlusExpression n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals("int") || !ret2.equals("int"))
         {
            police.throwType(" in PlusExpression");
         }
         _ret = (R)("int");
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "-"
    * f2 -> PrimaryExpression()
    */
   public R visit(MinusExpression n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals("int") || !ret2.equals("int"))
         {
            police.throwType(" in MinusExpression");
         }
         _ret = (R)("int");
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "*"
    * f2 -> PrimaryExpression()
    */
   public R visit(TimesExpression n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals("int") || !ret2.equals("int"))
         {
            police.throwType(" in TimesExpression");
         }
         _ret = (R)("int");
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "/"
    * f2 -> PrimaryExpression()
    */
   public R visit(DivExpression n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals("int") || !ret2.equals("int"))
         {
            police.throwType(" in DivExpression");
         }
         _ret = (R)("int");
      }
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "["
    * f2 -> PrimaryExpression()
    * f3 -> "]"
    */
   public R visit(ArrayLookup n, A argu) {
      R _ret=null;
      String ret1 = "";
      String ret2 = "";
      ret1 = (String)n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      ret2 = (String)n.f2.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals("int[]") || !ret2.equals("int"))
         {
            police.throwType(" in ArrayLookup");
         }
         _ret = (R)"int";
      }
      n.f3.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "."
    * f2 -> "length"
    */
   public R visit(ArrayLength n, A argu) {
      R _ret=null;
      String ret1 = "";
      ret1 = (String)n.f0.accept(this, argu);
      if(((String)argu).equals("two"))
      {
         if(!ret1.equals("int[]"))
         {
            police.throwType("in ArrayLength");
         }
         _ret = (R)"int";
      }
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> PrimaryExpression()
    * f1 -> "."
    * f2 -> Identifier()
    * f3 -> "("
    * f4 -> ( ExpressionList() )?
    * f5 -> ")"
    */
   public R visit(MessageSend n, A argu) {
      R _ret=null;
      String fargs = "";
      R cname = n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      R fname = n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      fargs = (String)n.f4.accept(this, argu);
      n.f5.accept(this, argu);

      if(((String)argu).equals("two"))
      {
         
         StringTokenizer st = new StringTokenizer("");
         if(n.f4.present())
         {
            st = new StringTokenizer((String)fargs,",");
         }

         ArrayList<String> signature = new ArrayList<String>();
         while(st.hasMoreTokens())
         {
            signature.add(st.nextToken());
         }

         if(((String)cname).equals("this"))
         {
            //Method call within current scope-this is redundant now
            if(!T.verifySignature(T.curr_c.className, (String)fname, signature))
            {
               police.throwType(" in MessageSend, valid class not found");
            }
            _ret = (R)T.getReturnType(T.curr_c.className,(String)fname,signature);
         }
         else
         {
            //Arbitrary method call of another class
            //Get the class of the current object
            if(!T.findClass((String)cname))police.throwType(" in MessageSend::class not found");
            if(!T.verifySignature((String)cname, (String)fname, signature))
            {
               police.throwType(" in MessageSend given method call is invalid");
            }
            _ret = (R)T.getReturnType(cname.toString(),(String)fname,signature);
         }

      }
      return _ret;
   }

   /**
    * f0 -> Expression()
    * f1 -> ( ExpressionRest() )*
    */
   public R visit(ExpressionList n, A argu) {
      R _ret = (R)"";
      String farg = (String)n.f0.accept(this, argu);
      if(((String)argu).equals("two")) 
      {
          if(n.f1.present())
          {
              for(int i=0;i<n.f1.size();++i)
              {
                  farg +=(String)n.f1.elementAt(i).accept(this, argu);
              }
          }  
          _ret = (R)farg;
      }
      return _ret;
   }

   /**
    * f0 -> ","
    * f1 -> Expression()
    */
   public R visit(ExpressionRest n, A argu) {
      R _ret=(R)"";
      String farg = (String)n.f0.accept(this, argu);
      farg = farg + (String)n.f1.accept(this, argu);
      if(((String)argu).equals("two"))_ret = (R)farg;
      return _ret;
   }

   /**
    * f0 -> IntegerLiteral()
    *       | TrueLiteral()
    *       | FalseLiteral()
    *       | Identifier()
    *       | ThisExpression()
    *       | ArrayAllocationExpression()
    *       | AllocationExpression()
    *       | NotExpression()
    *       | BracketExpression()
    */
   public R visit(PrimaryExpression n, A argu) {
      R _ret=null;
      _ret = n.f0.accept(this, argu);
      if(argu.toString().equals("two"))
      {
         if(n.f0.which==3)
         {
            //return the class of the given Identifier
            if(!T.findVariable((String)_ret))
            {
               police.throwType("in PrimaryExpression Class of "+ _ret.toString()); 
            }
            _ret = (R)T.getType((String)_ret);
         }
      }
      return _ret;
   }

   /**
    * f0 -> <INTEGER_LITERAL>
    */
   public R visit(IntegerLiteral n, A argu) {
      R _ret=(R)"int";
      n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "true"
    */
   public R visit(TrueLiteral n, A argu) {
      R _ret=(R)"boolean";
      n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "false"
    */
   public R visit(FalseLiteral n, A argu) {
      R _ret=(R)"boolean";
      n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> <IDENTIFIER>
    */
   public R visit(Identifier n, A argu) {
      R _ret=null;
      _ret = (R)n.f0.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "this"
    */
   public R visit(ThisExpression n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      _ret = (R)T.curr_c.className;
      return _ret;
   }

   /**
    * f0 -> "new"
    * f1 -> "int"
    * f2 -> "["
    * f3 -> Expression()
    * f4 -> "]"
    */
   public R visit(ArrayAllocationExpression n, A argu) {
      R _ret=null;
      String chk = "";
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      n.f2.accept(this, argu);
      chk = (String)n.f3.accept(this, argu);
      if(argu.toString().equals("two"))
      {
         if(!chk.equals("int"))police.throwType("in ArrayAllocation");
         _ret = (R)"int[]";
      }
      n.f4.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "new"
    * f1 -> Identifier()
    * f2 -> "("
    * f3 -> ")"
    */
   public R visit(AllocationExpression n, A argu) {
      R _ret=null;
      String class_name = "";
      n.f0.accept(this, argu);
      class_name = (String)n.f1.accept(this, argu);
      if(argu.toString().equals("two"))
      {
         if(!T.findClass(class_name)){
            police.throwSymbol("in AllocationExpression:: " + class_name);
         }
         _ret = (R)class_name;
      }
      n.f2.accept(this, argu);
      n.f3.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> "!"
    * f1 -> Expression()
    */
   public R visit(NotExpression n, A argu) {
      R _ret=null;
      String ret1= "";
      n.f0.accept(this, argu);
      ret1 = (String)n.f1.accept(this, argu);
      if(argu.toString().equals("two"))
      {
         if(!ret1.equals("boolean"))police.throwType("in NotExpression" + ret1);
         _ret = (R)ret1;
      }
      return _ret;
   }

   /**
    * f0 -> "("
    * f1 -> Expression()
    * f2 -> ")"
    */
   public R visit(BracketExpression n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      if(argu.toString().equals("two"))_ret = n.f1.accept(this, argu);
      else n.f1.accept(this,argu);
      n.f2.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> Identifier()
    * f1 -> ( IdentifierRest() )*
    */
   public R visit(IdentifierList n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      return _ret;
   }

   /**
    * f0 -> ","
    * f1 -> Identifier()
    */
   public R visit(IdentifierRest n, A argu) {
      R _ret=null;
      n.f0.accept(this, argu);
      n.f1.accept(this, argu);
      return _ret;
   }

}