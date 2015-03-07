/*
 * args: -src [source_directory_of_your_classes] -dest [generator_output_directory]
 * Generator should iterate over all files in the -src and generate C++ sugar code 
 * which will magically work with files provided in src/system 
 * src/system provides memory and multi_index_container based on boost libraries 
 * boost is multi platform C++ library 
 */
package com.mpclmi.generator;

import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * @author vvenedict@gmail.com
 */
public class Generator
{
 
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       
        // TODO load class file and using reflexion
        // generate JNI and C++ code
        String className = args[0] ;
        Class clazz = null;
        try {
            clazz = Class.forName(className);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(Generator.class.getName()).log(Level.SEVERE, null, ex);
        }
       
        //Generate C++ code
        com.mpclmi.generator.cpp.Generator cpp_generator =
            new com.mpclmi.generator.cpp.Generator() ;
        new Container(clazz).accept(cpp_generator);
        new Index(clazz).accept(cpp_generator);
        
        
        //Generate Java code
         com.mpclmi.generator.java.Generator jgenerator =
            new com.mpclmi.generator.java.Generator() ;
        new Container(clazz).accept(jgenerator);
        new Index(clazz).accept(jgenerator);
        
        
    }
 
     
}

