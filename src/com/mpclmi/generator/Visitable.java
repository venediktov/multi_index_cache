
package com.mpclmi.generator; 
 
/**
*
* @author vvenedict@gmail.com
*/
 
public interface Visitable {
      
        //public abstract <R> R accept(Visitor<R> visitor);
    public void accept(Visitor visitor);
}
