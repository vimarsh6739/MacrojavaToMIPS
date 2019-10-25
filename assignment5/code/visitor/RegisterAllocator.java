/**
 * @author Vimarsh Sathia
 * 
 */

package visitor;
import syntaxtree.*;
import java.util.*;

class SymbolTable{

    HashMap<String, MethodTable> mlist;
    MethodTable curr_method;
    
    SymbolTable(){
        mlist = new HashMap<String,MethodTable>();
        curr_method = null;
    }

    void addMethod(String fName, String argCnt){
        MethodTable mobj = new MethodTable(fName,argCnt);
        mlist.put(fName, mobj);
    }

    void debugOutput(){
        mlist.forEach((k,v)->v.debugOutput());
    }
    
}

class MethodTable{

    String fName;
    LinkedHashMap<String,BlockTable> lbl_list;
    LinkedHashMap<Integer,BlockTable> block_list;
    int blockCnt;
    String argCnt;

    BlockTable curr_block;
    String curr_label;
    
    MethodTable(){
        fName = null;
        argCnt = null;
        curr_block = null;
        blockCnt = 0;
        curr_label = null;
        lbl_list = new LinkedHashMap<String,BlockTable>();
        block_list = new LinkedHashMap<Integer,BlockTable>();
    }

    MethodTable(String fName,String argCnt){
        this.fName = fName;
        this.argCnt = argCnt;
        this.curr_block = null;
        this.blockCnt = 0;
        this.curr_label = null;
        lbl_list = new LinkedHashMap<String,BlockTable>();
        block_list = new LinkedHashMap<Integer,BlockTable>();
    }

    void setBlock(int addr){curr_block = block_list.get(addr);}
    void resetBlock(){curr_block = null;}

    //returns the generated counter for scoping
    int addBlock(){
        BlockTable node;
        if(this.curr_label != null)node = lbl_list.get(curr_label);
        else node = new BlockTable();
        block_list.put(blockCnt,node);
        return blockCnt++;
    }

    //add entry to label list or set the value of curr_label if already present
    void addLabel(String label){
        if(lbl_list.containsKey(label)){this.curr_label = label;}
        else{
            BlockTable node = new BlockTable(label);
            lbl_list.put(label,node);
        }
    }

    void analyzeLiveness(){
        
        boolean flag = true;
        do{
            //Iterate and evaluate in,in1,out,out1
            
            //Check exit condition
            
        }while(flag);
    }
    
    void doLinearScan(){

    }

    void debugOutput(){
        System.out.println("#################"+ this.fName+"####################");
        block_list.forEach((k,v)->{System.out.println("Block " + (1+k.intValue()) + "::");v.debugOutput();});
    }

}

class BlockTable{

    LinkedHashSet<String> use;
    LinkedHashSet<String> def;
    LinkedHashSet<String> in;
    LinkedHashSet<String> out;
    LinkedHashSet<String> in1;
    LinkedHashSet<String> out1;
    
    String label;

    BlockTable(){
        label = null;
        use = new LinkedHashSet<>();
        def = new LinkedHashSet<>();
        in = new LinkedHashSet<>();
        out = new LinkedHashSet<>();
        in1 = new LinkedHashSet<>();
        out1 = new LinkedHashSet<>();
    }

    BlockTable(String label){
        this.label = label;
        use = new LinkedHashSet<>();
        def = new LinkedHashSet<>();
        in = new LinkedHashSet<>();
        out = new LinkedHashSet<>();
        in1 = new LinkedHashSet<>();
        out1 = new LinkedHashSet<>();
    }

    void addDef(String temp){this.def.add(temp);}
    void addUse(String temp){this.use.add(temp);}
    boolean checkSets(){return in.equals(in1) && out.equals(out1);}

    void debugOutput(){

        if(label!=null)System.out.println("Label:"+label);
        System.out.print("Def:\n");
        for(String i: def){
            System.out.println("\t" + i);
        }
        System.out.println();
        System.out.print("Use:\n");
        for(String i: use){
            System.out.println("\t" + i);
        }
        System.out.println();
    }

}

@SuppressWarnings("unchecked")
public class RegisterAllocator<R,A> extends GJDepthFirst<R,A> {

    SymbolTable T = new SymbolTable();

    public R visit(NodeToken n, A argu) { return (R)n.tokenImage; }

    /**
    * f0 -> "MAIN"
    * f1 -> StmtList()
    * f2 -> "END"
    * f3 -> ( Procedure() )*
    * f4 -> <EOF>
    */
    public R visit(Goal n, A argu) {
        R _ret=null;

        n.f0.accept(this,(A)"1");
        T.addMethod("MAIN","0");
        T.curr_method = T.mlist.get("MAIN");
        n.f1.accept(this,(A)"1");
        n.f2.accept(this,(A)"1");
        
        
        //Do liveness analysis here
        T.curr_method.analyseLiveness();
        T.curr_method.doLinearScan();
        
        T.curr_method = null;
        n.f3.accept(this,(A)"1");
        n.f4.accept(this,(A)"1");
        
        //complete second pass for code generation
        
        n.f0.accept(this,(A)"2");
        T.curr_method = T.mlist.get("MAIN");
        n.f1.accept(this,(A)"2");
        n.f2.accept(this,(A)"2");
        T.curr_method = null;
        n.f3.accept(this,(A)"2");
        n.f4.accept(this,(A)"2");

        T.debugOutput();
        return _ret;
    }

    /**
    * f0 -> ( ( Label() )? Stmt() )*
    */
    public R visit(StmtList n, A argu) {
        R _ret=null;
        String label = "";

        if(n.f0.present()){
            //Check if a label is there
            for(int i=0;i<n.f0.size();++i){

                //Label->check it
                if(((NodeOptional)((NodeSequence)n.f0.elementAt(i)).elementAt(0)).present()){
                    label = (String) ((NodeSequence)n.f0.elementAt(i)).elementAt(0).accept(this,argu);
                    if(argu.toString().equals("1")){
                        T.curr_method.addLabel(label);
                        T.curr_method.curr_label = label;
                    }
                } else { label = ""; }  

                //Stmt->accept it
                ((NodeSequence)n.f0.elementAt(i)).elementAt(1).accept(this,argu);
                if(argu.toString().equals("1")){
                    T.curr_method.curr_label = null;
                }
            }
        }

        return _ret;
    }

    /**
    * f0 -> Label()
    * f1 -> "["
    * f2 -> IntegerLiteral()
    * f3 -> "]"
    * f4 -> StmtExp()
    */
    public R visit(Procedure n, A argu) {
        R _ret=null;
        String fName = "";
        String argCnt = "";

        switch(argu.toString()){
            
            case "1": 
            
            fName = (String)n.f0.accept(this, argu);
            n.f1.accept(this, argu);
            argCnt = (String)n.f2.accept(this, argu);
            n.f3.accept(this, argu);
            T.addMethod(fName,argCnt);
            T.curr_method = T.mlist.get(fName);
            n.f4.accept(this, argu);
            T.curr_method = null;

            //Do liveness analysis
            T.curr_method.analyzeLiveness();
            //Do register allocation
            T.curr_method.doLinearScan();

            break;

            case "2":
            n.f0.accept(this, argu);
            n.f1.accept(this, argu);
            n.f2.accept(this, argu);
            n.f3.accept(this, argu);
            n.f4.accept(this, argu);
            break;
        }
        return _ret;
    }

    /**
    * f0 -> NoOpStmt()
    *       | ErrorStmt()
    *       | CJumpStmt()
    *       | JumpStmt()
    *       | HStoreStmt()
    *       | HLoadStmt()
    *       | MoveStmt()
    *       | PrintStmt()
    */
    public R visit(Stmt n, A argu) {
        R _ret=null;
        n.f0.accept(this, argu);
        return _ret;
    }

    /**
    * f0 -> "NOOP"
    */
    public R visit(NoOpStmt n, A argu) {
        R _ret=null;
        if(argu.toString().equals("1")){int index = T.curr_method.addBlock();}
        n.f0.accept(this, argu);
        return _ret;
    }

    /**
    * f0 -> "ERROR"
    */
    public R visit(ErrorStmt n, A argu) {
        R _ret=null;
        if(argu.toString().equals("1")){int index = T.curr_method.addBlock();}
        n.f0.accept(this, argu);
        return _ret;
    }

    /**
    * f0 -> "CJUMP"
    * f1 -> Temp()
    * f2 -> Label()
    */
    public R visit(CJumpStmt n, A argu) {
        R _ret=null;
        String tmp = "";
        String label = "";
        int index = 0;

        if(argu.toString().equals("1")){
            index = T.curr_method.addBlock();
            T.curr_method.setBlock(index);
        }
        n.f0.accept(this, argu);
        
        tmp = (String)n.f1.accept(this, argu);
        label = (String)n.f2.accept(this, argu);
        
        if(argu.toString().equals("1")){
            T.curr_method.curr_block.addUse(tmp);
            T.curr_method.addLabel(label);
            T.curr_method.resetBlock();
        }
        return _ret;
    }

    /**
    * f0 -> "JUMP"
    * f1 -> Label()
    */
    public R visit(JumpStmt n, A argu) {
        R _ret=null;
        String label = "";
        int index = 0;
        if(argu.toString().equals("1")){
            index = T.curr_method.addBlock();
            T.curr_method.setBlock(index);
        }
        n.f0.accept(this, argu);
        label = (String)n.f1.accept(this, argu);

        if(argu.toString().equals("1")){
            T.curr_method.addLabel(label);
            T.curr_method.resetBlock();
        }
        return _ret;
    }

    /**
    * f0 -> "HSTORE"
    * f1 -> Temp()
    * f2 -> IntegerLiteral()
    * f3 -> Temp()
    */
    public R visit(HStoreStmt n, A argu) {
        R _ret=null;
        String tmp1 ="";
        String tmp2 = "";
        if(argu.toString().equals("1")){
            T.curr_method.setBlock(T.curr_method.addBlock());
        }

        n.f0.accept(this, argu);
        tmp1 = (String)n.f1.accept(this, argu);
        n.f2.accept(this, argu);
        tmp2 = (String)n.f3.accept(this, argu);
        
        if(argu.toString().equals("1")){
            T.curr_method.curr_block.addUse(tmp1);
            T.curr_method.curr_block.addUse(tmp2);
            T.curr_method.resetBlock();
        }

        return _ret;
    }

    /**
    * f0 -> "HLOAD"
    * f1 -> Temp()
    * f2 -> Temp()
    * f3 -> IntegerLiteral()
    */
    public R visit(HLoadStmt n, A argu) {
        //def
        R _ret=null;
        String tmp1 ="";
        String tmp2 = "";
        
        if(argu.toString().equals("1")){
            T.curr_method.setBlock(T.curr_method.addBlock());
        }

        n.f0.accept(this, argu);
        tmp1 = (String)n.f1.accept(this, argu);
        tmp2 = (String)n.f2.accept(this, argu);
        n.f3.accept(this, argu);

        if(argu.toString().equals("1")){
            T.curr_method.curr_block.addDef(tmp1);
            T.curr_method.curr_block.addUse(tmp2);
            T.curr_method.resetBlock();
        }

        return _ret;
    }

    /**
    * f0 -> "MOVE"
    * f1 -> Temp()
    * f2 -> Exp()
    */
    public R visit(MoveStmt n, A argu) {
        //def
        R _ret=null;
        String tmp1 = "";
        if(argu.toString().equals("1")){
            T.curr_method.setBlock(T.curr_method.addBlock());
        }
        
        n.f0.accept(this, argu);
        tmp1 = (String)n.f1.accept(this, argu);
        n.f2.accept(this, argu);

        if(argu.toString().equals("1")){
            T.curr_method.curr_block.addDef(tmp1);
            T.curr_method.resetBlock();
        }

        return _ret;
    }

    /**
    * f0 -> "PRINT"
    * f1 -> SimpleExp()
    */
    public R visit(PrintStmt n, A argu) {
        R _ret=null;
        
        if(argu.toString().equals("1")){
            T.curr_method.setBlock(T.curr_method.addBlock());
        }

        n.f0.accept(this, argu);
        n.f1.accept(this, argu);

        if(argu.toString().equals("1")){
            T.curr_method.resetBlock();
        }

        return _ret;
    }

    /**
    * f0 -> Call()
    *       | HAllocate()
    *       | BinOp()
    *       | SimpleExp()
    */
    public R visit(Exp n, A argu) {
        
        R _ret=null;
        n.f0.accept(this, argu);
        return _ret;
    }

    /**
    * f0 -> "BEGIN"
    * f1 -> StmtList()
    * f2 -> "RETURN"
    * f3 -> SimpleExp()
    * f4 -> "END"
    */
    public R visit(StmtExp n, A argu) {
        R _ret=null;
        switch(argu.toString()){

            case "1":
            n.f0.accept(this, argu);
            n.f1.accept(this, argu);
            n.f2.accept(this, argu);
            int addr = T.curr_method.addBlock();
            T.curr_method.setBlock(addr);
            n.f3.accept(this, argu);
            n.f4.accept(this, argu);
            T.curr_method.resetBlock();
            break;
            
            case "2":
            n.f0.accept(this, argu);
            n.f1.accept(this, argu);
            n.f2.accept(this, argu);
            n.f3.accept(this, argu);
            n.f4.accept(this, argu);
            break;

            default:
            //do nothing
        }
        return _ret;
    }

    /**
    * f0 -> "CALL"
    * f1 -> SimpleExp()
    * f2 -> "("
    * f3 -> ( Temp() )*
    * f4 -> ")"
    */
    public R visit(Call n, A argu) {
        R _ret=null;
        String tmp;
        n.f0.accept(this, argu);
        n.f1.accept(this, argu);
        n.f2.accept(this, argu);

        if(n.f3.present()){
            for(int i=0;i<n.f3.size();++i){
                tmp = (String)((Node)n.f3.elementAt(i)).accept(this,argu);
                if(argu.toString().equals("1")){
                    T.curr_method.curr_block.addUse(tmp);
                }
            }
        }

        n.f4.accept(this, argu);
        return _ret;
    }

    /**
    * f0 -> "HALLOCATE"
    * f1 -> SimpleExp()
    */
    public R visit(HAllocate n, A argu) {
        R _ret=null;
        n.f0.accept(this, argu);
        n.f1.accept(this, argu);
        return _ret;
    }

    /**
    * f0 -> Operator()
    * f1 -> Temp()
    * f2 -> SimpleExp()
    */
    public R visit(BinOp n, A argu) {
        R _ret=null;
        String temp = "";
        n.f0.accept(this, argu);
        temp = (String)n.f1.accept(this, argu);
        
        if(argu.toString().equals("1")){
            T.curr_method.curr_block.addUse(temp);    
        }

        n.f2.accept(this, argu);
        
        return _ret;
    }

    /**
    * f0 -> "LE"
    *       | "NE"
    *       | "PLUS"
    *       | "MINUS"
    *       | "TIMES"
    *       | "DIV"
    */
    public R visit(Operator n, A argu) {
        R _ret=null;
        n.f0.accept(this, argu);
        return _ret;
    }

    /**
    * f0 -> Temp()
    *       | IntegerLiteral()
    *       | Label()
    */
    public R visit(SimpleExp n, A argu) {
        R _ret=null;
        _ret = n.f0.accept(this, argu);
        if(n.f0.which == 0){
            //save temp as a def
            if(argu.toString().equals("1")){T.curr_method.curr_block.addUse((String)_ret);}
        }
        return _ret;
    }

    /**
    * f0 -> "TEMP"
    * f1 -> IntegerLiteral()
    */
    public R visit(Temp n, A argu) {
        R _ret=null;
        String tmp = "";
        String val = "";
        
        tmp = (String)n.f0.accept(this, argu);
        val = (String)n.f1.accept(this, argu);
        _ret = (R)(tmp+val);
        return _ret;
    }

    /**
    * f0 -> <INTEGER_LITERAL>
    */
    public R visit(IntegerLiteral n, A argu) {
        R _ret=null;
        _ret = n.f0.accept(this, argu);
        return _ret;
    }

    /**
    * f0 -> <IDENTIFIER>
    */
    public R visit(Label n, A argu) {
        R _ret=null;
        _ret = n.f0.accept(this, argu);
        return _ret;
    }

}
