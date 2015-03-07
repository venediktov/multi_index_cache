
package com.mpclmi.generator.cpp;

import java.lang.annotation.Annotation;

/**
 *
 * The accept of Index class does not accept a Visitor rather 
 * sends Visitor to Composite or Single index depending on annotation type
 *
 * @author vvenedict@gmail.com
 */
 
public class Index implements  Visitable  {
    private final Annotation[] _indexes;
    public Index(Class clazz) { 
        _indexes = clazz.getAnnotationsByType(com.mpclmi.annotations.CacheIndex.class) ;
    }
   
    @Override
    public void accept(Visitor visitor) {
        for ( Annotation a : _indexes) {
            //if fields size in Annotation is = 1 then Single
            new SingleIndex(a).accept(visitor);
            //else if > 1 then compisite  
            new CompositeIndex(a).accept(visitor);
        }
    }
}

