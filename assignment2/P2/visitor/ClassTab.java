package visitor;

import syntaxtree.*;
import java.util.*;

public class ClassTab 
{
    public ErrorThrower police = new ErrorThrower();
    public HashMap<String,FunctionTab> fnList;
    public HashMap<String,String> cfList;
    public String classParent;
    public String className;

    public ClassTab()
    {
    }

    public ClassTab(String name)
    {
        fnList = new HashMap<String, FunctionTab>();
        cfList = new HashMap<String,String>();
        this.className = name;
        this.classParent = "";
    }

    public ClassTab(String name,String parent)
    {
        fnList = new HashMap<String, FunctionTab>();
        cfList = new HashMap<String,String>();
        this.className = name;
        this.classParent=parent;
    }

    public void insertCField(String type,String id)
    {
        if(!cfList.containsKey(id))
        {
            cfList.put(id,type);
        }
        else
        {
            police.throwType("in insertCField(type,id)");
        }
    }

    public void insertFunction(String fname, String rtype)
    {
        FunctionTab objf = new FunctionTab(fname,rtype);

        //No overloading allowed!
        if(!this.fnList.containsKey(fname))
        {
            this.fnList.put(fname,objf);
        }
        else
        {
            this.police.throwType("in insertFunction()");
        }
    }

    public boolean findFunction(String fname)
    {
        return fnList.containsKey(fname);
    }

    public boolean testSuperClass(String sup, String  chld,SymTab T)
    {
        if(T.cList.get(chld)==null)
        {
            System.out.println(sup);
            System.out.println(chld);
            System.out.println("~~~~~~~~~~~~~~");
            return false;
        }
        if(T.cList.get(chld).classParent.equals(""))return false;
        else if(T.cList.get(chld).classParent.equals(sup))return true;
        else return this.testSuperClass(sup,T.cList.get(chld).classParent,T);
    }

    public boolean verifySignature(String fname, ArrayList<String> sgn, SymTab T)
    {
        FunctionTab ft = fnList.get(fname);
        int s1 = sgn.size();
        int s2 = ft.argTypeList.size();
        if(s1!=s2)return false;
        else
        {
            boolean flag = true;
            for(int i=0;i<s1;++i)
            {
            if(!(sgn.get(i).equals(ft.argTypeList.get(i))))
            {
                if(sgn.get(i).equals("int") || sgn.get(i).equals("int[]") || sgn.get(i).equals("boolean"))
                {
                    flag = false;
                    break;
                }
                else
                {
                    //check if the ft.argTypeList.get(i) is a superclass of sgn.get(i) if yes then dont change flag
                    flag = this.testSuperClass(ft.argTypeList.get(i),sgn.get(i),T);
                    if(!flag)break;
                }
            }
            }
            return flag;
        }
    }

    public String getReturnType(String fname, ArrayList<String> sgn)
    {
        //Only called if the function has been verified with the given signature
        return this.fnList.get(fname).returnType;
    }

}
