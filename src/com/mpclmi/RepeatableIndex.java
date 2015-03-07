/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.mpclmi;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 *
 * @author vvenedik
 */
@Retention(RetentionPolicy.RUNTIME)
public @interface RepeatableIndex {
    public CacheIndex [] value();
}