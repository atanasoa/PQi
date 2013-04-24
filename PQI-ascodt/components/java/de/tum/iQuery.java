//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package de.tum;


public interface iQuery  {
  class IntegerWrapper {
    public int value;
  }
  class DoubleWrapper {
    public double value;
  }
  class StringWrapper {
    public String value;
  }
  class BooleanWrapper {
    public boolean value;
  }
  public long getReference();
  //void lock();
 
  //void unlock();
  

  public void requestNumberOfParts(int parts[]);

  public void requestPartsInformation(double offset[],double size[],int dimensions[],int identifiers[]);


}
 

