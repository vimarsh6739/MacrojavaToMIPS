
package visitor;

import syntaxtree.*;
import java.util.*;

class FunctionTab 
{
    ErrorThrower police = new ErrorThrower();

    ArrayList<String> argList;
    ArrayList<String> argTypeList;
    
    HashMap<String,String> ffList;
    String returnType;
    String className;

    FunctionTab()
    {
    }

    FunctionTab(String className,String rtype)
    {
        argList = new ArrayList<String>();
        argTypeList = new ArrayList<String>();
        ffList = new HashMap<String,String>();
        returnType = rtype;
        this.className = className;
    }

    void insertFField(String type,String id)
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

    void insertArgument(String type, String id)
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

    String getArgumentType(String val)
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