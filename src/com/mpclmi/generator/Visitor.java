
package com.mpclmi.generator; 
 
/**
*
* @author vvenedict@gmail.com
* TODO: see if java can offer better way , not to list 
* all of visit methods , maybe reflective visitor pattern ?
*/
public interface Visitor {
   
    public void visit(Container c);
    public void visit(SingleIndex s);
    public void visit(CompositeIndex ci) ;
   
}
 
