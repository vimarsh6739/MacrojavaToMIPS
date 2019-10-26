/**
 * @author Vimarsh Sathia
 * 
 */

package visitor;
import syntaxtree.*;
import java.util.*;

class Tuple {

    public String var;
    public int first;
    public int second;
    public int isArg;
    public Tuple(){
        this.var = "";
        this.first = 0;
        this.second = 0;
    }

    public Tuple(String var,int first,int second){
        this.var = var;
        this.first = first;
        this.second = second;
    }

    public void print(){
        if(isArg == 0){
            System.out.println(" is a value from "+this.first + " to " + this.second);
        }
        else{
            System.out.println(" is an argument from "+this.first + " to " + this.second);
        }
    }

}
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

    void debugUseDef(){
        mlist.forEach((k,v)->v.debugUseDef());
    }
    
}

class MethodTable{

    String fName;
    LinkedHashMap<String,BlockTable> lbl_list;
    LinkedHashMap<Integer,BlockTable> block_list;
    int maxArgCnt;
    int blockCnt;
    int allRegCnt;

    String [] allRegs;
    String argCnt;
    boolean spillFlag;

    BlockTable curr_block;
    String curr_label;
    
    LinkedHashSet<String> allTemps;
    LinkedHashMap<String,Tuple> liveIntervalMap;
    LinkedHashMap<String,String> reg_map;
    /**
     * To do- 
     * 
     */

    MethodTable(){
        this.fName = null;
        this.argCnt = null;
        this.curr_block = null;
        this.maxArgCnt = 0;
        this.blockCnt = 0;
        this.curr_label = null;
        this.lbl_list = new LinkedHashMap<String,BlockTable>();
        this.block_list = new LinkedHashMap<Integer,BlockTable>();
        this.liveIntervalMap = new LinkedHashMap<String,Tuple>();
        this.allTemps = new LinkedHashSet<String>();
        this.spillFlag = false;
        this.allRegs = new String[]{"s0","s1","s2","s3","s4","s5","s6","s7","t0","t1","t2","t3","t4","t5","t6","t7","t8","t9"};
        this.allRegCnt = this.allRegs.length;
        this.reg_map = new LinkedHashMap<String,String>();
    }

    MethodTable(String fName,String argCnt){
        this.fName = fName;
        this.argCnt = argCnt;
        this.curr_block = null;
        this.blockCnt = 0;
        this.curr_label = null;
        this.lbl_list = new LinkedHashMap<String,BlockTable>();
        this.block_list = new LinkedHashMap<Integer,BlockTable>();
        this.liveIntervalMap = new LinkedHashMap<String,Tuple>();
        this.allTemps = new LinkedHashSet<String>();
        this.spillFlag = false;
        this.allRegs = new String[]{"s0","s1","s2","s3","s4","s5","s6","s7","t0","t1","t2","t3","t4","t5","t6","t7","t8","t9"};
        this.allRegCnt = this.allRegs.length;
        this.reg_map = new LinkedHashMap<String,String>();
    }

    void setBlock(int addr){curr_block = block_list.get(addr);}
    void resetBlock(){curr_block = null;}

    //returns the generated index-also updates successor of previous block
    int addBlock(){
        BlockTable node;
        if(this.curr_label != null){
            node = lbl_list.get(curr_label);
        }
        else {
            node = new BlockTable();
        }
        if(block_list.containsKey(blockCnt-1)){
            //reversi!
            BlockTable parent = block_list.get(blockCnt-1);
            parent.addSucc(node);
        }
        block_list.put(blockCnt,node);

        return blockCnt++;
    }

    //add entry to label list or set the value of curr_label if already present
    void addLabel(String label){
        if(lbl_list.containsKey(label)){
            this.curr_label = label;
        }
        else{
            BlockTable node = new BlockTable(label);
            lbl_list.put(label,node);
        }
    }

    void analyzeLiveness(){

        //Uncomment for Debugging
        //System.out.println("Liveness for " + this.fName + "::");
        int iter=0;
        boolean flag = false;
        do{
            iter++;          
            flag = false;
            //Iterate and update in and out for every node 
            Iterator itr = block_list.entrySet().iterator();
            while(itr.hasNext()){
                Map.Entry pair= (Map.Entry)itr.next();
                Integer key = (Integer)pair.getKey();
                BlockTable node = (BlockTable)pair.getValue();
                //save in in1 & out in out1
                node.copySet(1);
                node.copySet(2);
                //redefine in
                node.updateIn();
                //redefine out
                node.updateOut();
            }

            //Check exit condition
            itr = block_list.entrySet().iterator();
            while(itr.hasNext()){

                Map.Entry pair= (Map.Entry)itr.next();
                Integer key = (Integer)pair.getKey();
                BlockTable node = (BlockTable)pair.getValue();

                flag = (flag) || !(node.checkSet());
            }
            //Uncomment for debugging
            //Debugging Liveness
            /* if(iter>=25){flag = false;break;}
            else{this.debugLiveness(iter);} */
                   
        }while(flag);
        //System.out.println("Iterations = " + iter);
        //Update live ranges
        this.updateLiveRanges();
        //this.debugLiveRanges();
    }

    int getEnd(String str){
        //return last in
        int ans = 0;
        for(int j = this.blockCnt - 1; j>=0; --j){
            if(block_list.get(j).in.contains(str)){ans = j;break;}
        }
        return ans;
    }

    int[] getStart(String str){
        //return use or def- whichever is earlier
        int []ans = new int[2];
        int ansUse = this.blockCnt;
        int ansDef = this.blockCnt;

        for(int j = 0;j<this.blockCnt;++j){
            if(block_list.get(j).def.contains(str)){ansDef = j;break;}
        }

        for(int j = 0;j<this.blockCnt;++j){
            if(block_list.get(j).use.contains(str)){ansUse = j;break;}
        }

        if(ansDef < ansUse){
            ans[0] = 0;
            ans[1] = ansDef;
            return ans;}
        else{
            ans[0] = 1;
            ans[1] = ansUse;
            return ans;
        }
    }
    
    void updateLiveRanges(){
        
        Iterator<String> itr = this.allTemps.iterator();
        
        while(itr.hasNext()){
            String str = itr.next();
            int[] arr = this.getStart(str);
            int start = arr[1];
            int end = this.getEnd(str);
            Tuple active_range = new Tuple(str,start,end);
            active_range.isArg = arr[0];
            liveIntervalMap.put(str, active_range);
        }
    }
    
    void doLinearScan(){

        //Perform linear scan register  allocation
        ArrayList<Tuple> liveIntervals = new ArrayList<Tuple>();
        ArrayList<Tuple> activeIntervals = new ArrayList<Tuple>();
        ArrayList<Integer> activeRegisters = new ArrayList<Integer>();//store index of active registers
        
        //maintain free register pool
        boolean [] freeRegPool = new boolean[18];
        for(int i=0;i<18;++i)freeRegPool[i] = true;

        //Build liveIntervals
        Iterator itr = liveIntervalMap.entrySet().iterator();
        while(itr.hasNext()){
            Map.Entry pair = (Map.Entry)itr.next();
            Tuple curr_range = (Tuple)pair.getValue();
            int pos=-1;
            //Iterate and search for correct position to insert
            for(int i = 0;i < liveIntervals.size();++i){
                if(liveIntervals.get(i).first > curr_range.first){
                    pos = i;
                    break;
                }
            }

            if(pos==-1){
                //add at the end
                liveIntervals.add(curr_range);
            }
            else{
                //add in between
                liveIntervals.add(pos,curr_range);
            }
        }

        for(int i = 0;i< liveIntervals.size();++i){
            //expire all old intervals
            for(int j = 0;j < activeIntervals.size();j++){
                if(activeIntervals.get(j).second >= liveIntervals.get(i).first){
                    break;
                }
                else{
                    //interval no longer active
                    freeRegPool[activeRegisters.get(j).intValue()]

                }
            }

            //check if we need to spill current register
            if(active.size() == this.allRegCnt){
                //spill

            }else{
                //assign a free register
            }
        }
    }

    void debugUseDef(){
        System.out.println("#################"+ this.fName+"####################");
        block_list.forEach((k,v)->{System.out.println("Block " + (1+k.intValue()) + "::");v.debugUseDef();});
    }

    void debugLiveness(int iter){
        Iterator itr = block_list.entrySet().iterator();
        System.out.println("#################Iteration " + iter + " ###############");
        while(itr.hasNext()){
            Map.Entry pair= (Map.Entry)itr.next();
            Integer key = (Integer)pair.getKey();
            BlockTable node = (BlockTable)pair.getValue();
            System.out.println("~~~~~~~~~~~~~~Block " + (key.intValue()) + "~~~~~~~~~~~~~");
            //Printing use
            System.out.print("Use -> ");
            System.out.println(node.use);
            //Printing def
            System.out.print("Def -> ");
            System.out.println(node.def);
            //Printing in1
            System.out.print("In1 -> ");
            System.out.println(node.in1);
            //Printing in
            System.out.print("In -> ");
            System.out.println(node.in);
            //Printing out1
            System.out.print("Out1 -> ");
            System.out.println(node.out1);
            //Printing out
            System.out.print("Out -> ");
            System.out.println(node.out);
        }
    }

    void debugLiveRanges(){
        System.out.println("#################"+ this.fName+"####################");
        liveIntervalMap.forEach((k,v)->{System.out.print("For " + k + "->");v.print();});
    }
}

class BlockTable{

    LinkedHashSet<String> use;
    LinkedHashSet<String> def;
    LinkedHashSet<String> in;
    LinkedHashSet<String> out;
    LinkedHashSet<String> in1;
    LinkedHashSet<String> out1;
    LinkedHashSet<BlockTable> succ;

    String label;

    BlockTable(){
        label = null;
        use = new LinkedHashSet<String>();
        def = new LinkedHashSet<String>();
        in = new LinkedHashSet<String>();
        out = new LinkedHashSet<String>();
        in1 = new LinkedHashSet<String>();
        out1 = new LinkedHashSet<String>();
        succ = new LinkedHashSet<BlockTable>();
    }

    BlockTable(String label){
        this.label = label;
        use = new LinkedHashSet<String>();
        def = new LinkedHashSet<String>();
        in = new LinkedHashSet<String>();
        out = new LinkedHashSet<String>();
        in1 = new LinkedHashSet<String>();
        out1 = new LinkedHashSet<String>();
        succ = new LinkedHashSet<BlockTable>();
    }

    void addDef(String temp){this.def.add(temp);}
    void addUse(String temp){this.use.add(temp);}
    void addSucc(BlockTable node){this.succ.add(node);}
    boolean checkSet(){return in1.equals(in) && out1.equals(out);}

    void copySet(int choice){
        if(choice==1){
            this.in1 = new LinkedHashSet<String>();
            Iterator<String> itr = this.in.iterator();
            while(itr.hasNext()){this.in1.add(itr.next());}
        }else{
            this.out1= new LinkedHashSet<String>();
            Iterator<String> itr = this.out.iterator();//reversi!
            while(itr.hasNext()){this.out1.add(itr.next());}
        }
    }

    void updateIn(){
        this.in =  new LinkedHashSet<String>();

        //add elements of use
        Iterator<String> itr = this.use.iterator();
        while(itr.hasNext()){
            this.in.add(itr.next());
        }
        
        LinkedHashSet noDefs = new LinkedHashSet<String>();
        
        itr = this.out.iterator();
        while(itr.hasNext()){
            String tmp = itr.next();
            if(!this.def.contains(tmp))noDefs.add(tmp);
        }
        //Take union
        itr = noDefs.iterator();
        while(itr.hasNext()){
            String temp = itr.next();
            if(!this.in.contains(temp)){this.in.add(temp);}
        }

    }

    void updateOut(){
        this.out = new LinkedHashSet<String>();
        //take union of in of successors and put it in out
        Iterator<BlockTable> itr = this.succ.iterator();
        while(itr.hasNext()){
            BlockTable child = itr.next();
            Iterator<String> itr2 = child.in.iterator();
            while(itr2.hasNext()){
                String temp = itr2.next();
                this.out.add(temp);
            }
        }
    }
    
    void debugUseDef(){

        if(label!=null)System.out.println("Label:"+label);
        System.out.print("Def:\n");
        System.out.println(this.def);
        System.out.print("Use:\n");
        System.out.println(this.use);
        System.out.println();
    }

}

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
        T.curr_method.analyzeLiveness();
        //Do register allocation here
        T.curr_method.doLinearScan();
        
        T.curr_method = null;
        n.f3.accept(this,(A)"1");
        n.f4.accept(this,(A)"1");
        
        //Do code generation here
        
        n.f0.accept(this,(A)"2");
        T.curr_method = T.mlist.get("MAIN");
        n.f1.accept(this,(A)"2");
        n.f2.accept(this,(A)"2");
        T.curr_method = null;
        n.f3.accept(this,(A)"2");
        n.f4.accept(this,(A)"2");

        //T.debugUseDef();
        System.out.println("Done !");
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
            

            //Do liveness analysis
            T.curr_method.analyzeLiveness();
            //Do register allocation
            T.curr_method.doLinearScan();
            T.curr_method = null;
            break;

            case "2":
            fName = (String)n.f0.accept(this, argu);
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
            //add label node as a successor to the current node
            T.curr_method.curr_block.addSucc(T.curr_method.lbl_list.get(label));
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
            T.curr_method.curr_block.addSucc(T.curr_method.lbl_list.get(label));
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
            if(argu.toString().equals("1")){T.curr_method.maxArgCnt = Math.max(T.curr_method.maxArgCnt,n.f3.size());}
            for(int i=0;i<n.f3.size();++i){
                tmp = (String)((Node)n.f3.elementAt(i)).accept(this,argu);
                if(argu.toString().equals("1")){T.curr_method.curr_block.addUse(tmp);}
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
        //This temp was used somwehere
        _ret = (R)(tmp+val);
        if(argu.toString().equals("1")){
            if(!T.curr_method.allTemps.contains(tmp+val)){
                T.curr_method.allTemps.add(tmp+val);
            } 
        }
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
