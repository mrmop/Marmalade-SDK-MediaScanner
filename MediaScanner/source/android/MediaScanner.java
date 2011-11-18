/*
java implementation of the MediaScanner extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import android.net.Uri;
import android.media.MediaScannerConnection;
import com.ideaworks3d.marmalade.*;
import com.ideaworks3d.marmalade.LoaderAPI;

class MediaScanner implements MediaScannerConnection.MediaScannerConnectionClient
{
    private MediaScannerConnection	m_Connection;
    private String					m_Path;
    private String					m_MimeType;

    public void Scan(String filepath, String mime_type)
    {
		m_Path = filepath;
		m_MimeType = mime_type;
		m_Connection = new MediaScannerConnection(LoaderActivity.m_Activity, this);
		m_Connection.connect();
    }
	public void onMediaScannerConnected()
	{
		m_Connection.scanFile(m_Path, m_MimeType);
	}

	public void onScanCompleted(String path, Uri uri)
	{
		m_Connection.disconnect();
		m_Connection = null;
	}
}
