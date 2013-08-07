//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package de.tum;


public abstract class SocketTestAAbstractJavaImplementation extends SocketComponent implements SocketTestA{
  protected de.tum.ascodt.plugin.ui.tabs.SocketClientAppsTab _appTab;
  protected String   _instanceName;
  protected String _projectLocation;
  public SocketTestAAbstractJavaImplementation( String instanceName ) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    _instanceName = instanceName;
    _appTab = new de.tum.ascodt.plugin.ui.tabs.SocketClientAppsTab("SocketTestA",this, de.tum.ascodt.plugin.ui.views.AppsViewContainer.ID);
    _appTab.setVisible(true);
    _appTab.addListener(this);
    
    
  }
  
  public de.tum.ascodt.repository.Target getTarget() {
     return de.tum.ascodt.repository.Target.createReverseCxxRemoteSocketTarget();
  }
  
  public de.tum.ascodt.repository.TargetParameters getTargetParameters(){
     return de.tum.ascodt.repository.TargetParameters.createRemoteSocketParameters(
          _appTab.getHost(),
          _appTab.getPort()
          );
  }

  public long getReference(){
    return 0;
  }  
  
  public void setReference(long ref){
   
  }
  
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void lock() {
    
  }

  public void setProjectLocation(String location){
     _projectLocation = location;
     _appTab.setProjectLocation(location);
     if(_appTab.hasApplicationSettings())
          _appTab.execute();
  }
 
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void unlock() {
    
  }
  
 
  public void destroy()  {
          try{
               if(isConnected())
                    sendIntData(1);
          }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
               de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError(getClass().getName(), "destroy()", e);
          }
          super.close();
          _appTab.removeListener(this);
          _appTab.setVisible(false);
          _appTab.dispose();
    
  }
  
  public boolean isValid() {
     return true;
  }


  public boolean hasGUI() {
    // @todo Insert your code here
    return false;
  }
  
  
  public void openGUI() {
    // @todo Insert your code here
  }
  
  
  public void closeGUI() {
    // @todo Insert your code here
  }
  
  @Override
  public String getInstanceName() {
    return _instanceName;
  }

  @Override
  public void setInstanceName(String instanceName) {
    _instanceName=instanceName;
  }
  
  public void createInstance(){
     
  }
 
  public void destroyInstance(){
  }
 
  

  public void getNumberOfParts(int parts[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=5;
         sendIntData(methodId);
         sendIntData(parts);

         readIntData(parts,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError( getClass().getName() , "getNumberOfParts()", e);
    }  
  }
  

  public void getQueryDescription(double offset[],double size[],int resolution[],int mids[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=6;
         sendIntData(methodId);
         sendIntData(offset.length);
sendDoubleData(offset);
sendIntData(size.length);
sendDoubleData(size);
sendIntData(resolution.length);
sendIntData(resolution);
sendIntData(mids.length);
sendIntData(mids);

         int offset_len;
offset_len=readIntData();
readDoubleData(offset,offset_len);
int size_len;
size_len=readIntData();
readDoubleData(size,size_len);
int resolution_len;
resolution_len=readIntData();
readIntData(resolution,resolution_len);
int mids_len;
mids_len=readIntData();
readIntData(mids,mids_len);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError( getClass().getName() , "getQueryDescription()", e);
    }  
  }
  

  public void forwardAnswer(final double data[],final double distance[],final int indices[],final int rid) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=7;
         sendIntData(methodId);
         sendIntData(data.length);
sendDoubleData(data);
sendIntData(distance.length);
sendDoubleData(distance);
sendIntData(indices.length);
sendIntData(indices);
sendIntData(rid);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError( getClass().getName() , "forwardAnswer()", e);
    }  
  }
  


}
 


