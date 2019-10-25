
package visitor;

import syntaxtree.*;
import java.util.*;

public class FunctionTab 
{
    public ErrorThrower police = new ErrorThrower();

    public ArrayList<String> argList;
    public ArrayList<String> argTypeList;
    
    public HashMap<String,String> ffList;
    public String returnType;
    public String className;

    public FunctionTab()
    {
    }

    public FunctionTab(String className,String rtype)
    {
        argList = new ArrayList<String>();
        argTypeList = new ArrayList<String>();
        ffList = new HashMap<String,String>();
        returnType = rtype;
        this.className = className;
    }

    public void insertFField(String type,String id)
    {
        if(!this.ffList.containsKey(id))
        {
            this.ffList.put(id,type);
        }
        else
        {
            police.throwType("in insertFField");
        }
    }

    public void insertArgument(String type, String id)
    {
        if(!this.argList.contains(id))
        {
            this.argList.add(id);
            this.argTypeList.add(type);
        }
        else
        {
            police.throwType("in insertArgument()");
        }
    }

    public String getArgumentType(String val)
    {
        //invoked iif we know val is in argList
        String ret = "";
        for(int i=0;i<argList.size();++i)
        {
            if(val.equals(argList.get(i)))
            {
            ret = argTypeList.get(i);
            break;
            }
        }
        return ret;
    }
}