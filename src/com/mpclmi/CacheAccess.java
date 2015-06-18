/*
 * These annotations change the memory model of generated Cache code 
 */
package com.mpclmi;

/**
 *
 * @author vvenedict@gmail.com
 */

public @interface CacheAccess {
    public enum Type {
        PRIVATE, SHARED, MEMORY_MAPPED
    }
    
    Type type() default Type.PRIVATE;
    String name()  ;
}
