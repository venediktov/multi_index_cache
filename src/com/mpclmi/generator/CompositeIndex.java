/*
 * @author vvenedict@gmail.com
 *
 * The idea  of what this class correspons to in C++ after
 * generator visits its contents is generating Complex index like :
 *
 * namespace com { namespace mpclmi { namespace generator {
 *    typedef boost::multi_index::ordered_non_unique<
 *    boost::multi_index::tag<$(variable)_tag>,
 *    boost::multi_index::composite_key< 
 *    container,
 *    BOOST_MULTI_INDEX_MEMBER(container,type,variable),
 *    BOOST_MULTI_INDEX_MEMBER(container,type,variable)
 *    > $(variable)_index_t ;
 *  }}}
 */

package com.mpclmi.generator.cpp;

import java.lang.annotation.Annotation;


public class CompositeIndex implements Visitable  {
   
    private final Annotation _a;
    public CompositeIndex(Annotation a) {
        _a = a;
        //TODO: inspect and process annotation and set up member variables
       // Boolean _is_unique = ( query Annotation for unique type  )
       //create isUnique() method will be called by Generator.java
       // String[]  _field_names = ( query Annotation for field names)

    }
    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
   
}
 
