/*
Generic implementation of the MediaScanner extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "MediaScanner_internal.h"
s3eResult MediaScannerInit()
{
    //Add any generic initialisation code here
    return MediaScannerInit_platform();
}

void MediaScannerTerminate()
{
    //Add any generic termination code here
    MediaScannerTerminate_platform();
}

void Scan(const char* filepath, const char* mime_type)
{
	Scan_platform(filepath, mime_type);
}
