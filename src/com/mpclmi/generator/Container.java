/*
 * This class serves as multi index container code generator 
 * @TODO: do some research on reflective visitor pattern 
 * 
 */

package com.mpclmi.generator;

import java.lang.annotation.Annotation;

/**
 *
 * @author vvenedict@gmail.com
 */
 
public class Container implements Visitable {
   private final Class _clazz;
   public Container(Class clazz) {
       Annotation cache_access = clazz.getDeclaredAnnotation(com.mpclmi.annotations.CacheAccess.class) ;
       //TODO: inspect and process annotation and set up member variables 
       // _access_level = ( query Annotation for acess level property ) 
       //create getAccessLevel() method will be called by Generator.java 
   }
      
   @Override
   public void accept(Visitor visitor)
   {
       visitor.visit(this);
   }
 
}
 
