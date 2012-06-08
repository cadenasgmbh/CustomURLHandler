/*
java implementation of the CustomURLHandler extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;
import com.ideaworks3d.marmalade.LoaderThread;
import android.net.Uri;
import android.content.Intent;
import java.lang.reflect.Field;
import java.lang.String;

class CustomURLHandler
{
    public void CustomURLHandlerRegister()
    {
        
    }
    
    public String CustomURLHandlerGetURL()
    {      
      try
      { 
        
        Class activitiyClass = Class.forName("com.ideaworks3d.marmalade.LoaderActivity");        
        Field activitiyField = activitiyClass.getField("m_Activity");                
        LoaderActivity activitiyObject = (LoaderActivity)activitiyField.get(activitiyClass);        
        Intent intent = activitiyObject.getIntent();
        
        
        /*
        Class LoaderThreadClass = Class.forName("com.ideaworks3d.marmalade.LoaderActivity");
        Field LoaderThreadSingleton = LoaderThreadClass.getField("g_Singleton");
        LoaderThread loaderthread = (LoaderThread)LoaderThreadSingleton.get(LoaderThreadClass);
        
        Field LoaderActivityMember = LoaderThreadClass.getDeclaredField("m_Loader");
        LoaderActivityMember.setAccessible(true); // hack to access private member
        LoaderActivity activitiyObject = (LoaderActivity)LoaderActivityMember.get(loaderthread);       
        
        Intent intent = activitiyObject.getIntent();
        */
        
        Uri uri = intent.getData();
        return uri.toString();
      }
      catch(Exception e)
      {
        System.out.println(e.getMessage());
      }
      //return new String("-N-O---U-R-L-");
      //return new "-N-O---U-R-L-";
      //return "-N-O---U-R-L-";
      //return new String("");
      //return "";
      return null;
    }
}
