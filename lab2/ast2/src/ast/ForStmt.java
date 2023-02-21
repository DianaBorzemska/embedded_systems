package ast;

public class ForStmt extends Node{
    public ForStmt(int pos) {
		super(pos);
		
	}

	@Override
	public String toString() {
		return "ForStmt ";
	}
	public String codeGen(Code c) {
		System.out.println("ForStmt -codegen");
        if (children.size()!=2)
        	System.out.println("need to a condition and a statment for for");
            	
		return null;
	}
	public Variable eval(Context c) {
			System.out.println("for  -eval");
			for (int ii=0;ii<children.size();ii++) {
				System.out.println(children.get(ii).getClass().getName());
			}
	        if (children.size()<2){
	        	System.out.println("need to a condition and a statment for for");}
				
			if(children.size()<4){
				Variable condition=children.get(0).eval(c);
				while(condition.val==1) {
					for (int ii=0;ii<children.size();ii++) {
						children.get(ii).eval(c);					
						condition=children.get(0).eval(c);
						
					}
					
				}
			}	
			else{
				children.get(0).eval(c);
				Variable condition=children.get(1).eval(c);
				
				
				while(condition.val==1) {               
					for (int ii=0;ii<children.size();ii++) {
						System.out.println("Value of 3rd" + children.get(3).eval(c));
						children.get(3).eval(c);					
						condition=children.get(1).eval(c);
					}
				}}
			
			
	        return null;
	}
}
