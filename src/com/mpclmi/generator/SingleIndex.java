
/*
 * @author vvenedict@gmail.com
 *
 * The idea  of what this class correspons to in C++ after
 * generator visits its contents is generating Complex index like :
 *
 *  typedef boost::multi_index::ordered_non_unique<
 *       boost::multi_index::tag<$(field)_tag>,
 *       BOOST_MULTI_INDEX_MEMBER(entry,field_type,field_name)
 *  > $(field)_index_t ;
 */

package com.mpclmi.generator;

import java.lang.annotation.Annotation;

public class SingleIndex implements  Visitable  {
    private final Annotation _a;
    public SingleIndex(Annotation a) {
        _a = a;
       //TODO: inspect and process annotation and set up member variables
       // Boolean _is_unique = ( query Annotation for unique type  )
       //create isUnique() method will be called by Generator.java
       // String _field_name = ( query Annotation for field name ) 
    }
   
 
    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}

