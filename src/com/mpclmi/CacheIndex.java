/*
 *  Application developer should be able to 
 *  create multiple indexes for the same record 
 *  The limitation of underlying library by defaul is 20 indexes 
 *  it seems enough for most applications , setting too many 
 *  indexes would slow down insertion time, so add indexes as needed, don't
 *  apply indexes only when it makes sense.
 *  the default number 20 can be increased and there will be provided 
 *  a switch in the build system where more then 20 can be applied. 
 */
package com.mpclmi;

import java.lang.annotation.Repeatable;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;


/**
 *
 * @author vvenedict@gmail.com
 */
@Retention(RetentionPolicy.RUNTIME)
@Repeatable(RepeatableIndex.class)
public @interface CacheIndex {
    public enum Type {
        UNIQUE, NON_UNIQUE
    }
    Type type() default Type.NON_UNIQUE;
    String [] fields() default "" ;
}

