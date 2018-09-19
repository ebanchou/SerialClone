// SerialClone.cpp
//
// Generated by C DriverWizard 3.2.0 (Build 2485)
// Requires DDK Only
// File created on 9/16/2005
//

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <setupapi.h>
#include <newdev.h>
#include "SerialCloneDll.h"

#if DBG
#define DbgOut(Text) OutputDebugString(TEXT("CoInstaller: " Text "\n"))
#else
#define DbgOut(Text) 
#endif 

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}


//DWORD  (CALLBACK* COINSTALLER_PROC)(
HRESULT SerialCloneCoInstall(
    IN DI_FUNCTION  InstallFunction,
    IN HDEVINFO  DeviceInfoSet,
    IN PSP_DEVINFO_DATA  DeviceInfoData  OPTIONAL,
    IN OUT PCOINSTALLER_CONTEXT_DATA  Context
    )
{
    switch (InstallFunction)
    {
    case DIF_INSTALLDEVICE: 
        if(!Context->PostProcessing) 
        {
            TCHAR       FriendlyName[30];
            BOOL        fSuccess=FALSE;
            DWORD       dwRegType, UINumber;

            DbgOut("DIF_INSTALLDEVICE");

            //
            // We wil create here a friendly name for this device
            // based on it's serial number.
            // The bus driver returns the serial No. in the UINumber.
            // field of the device capabiliities structure.
            // So let us get that first .
            //
            fSuccess =
            SetupDiGetDeviceRegistryProperty(DeviceInfoSet, 
                                             DeviceInfoData,
                                             SPDRP_UI_NUMBER,
                                             &dwRegType,
                                             (BYTE*) &UINumber,
                                             sizeof(UINumber),
                                             NULL);
            if (fSuccess)
            {
                //
                // Cook a FriendlyName and add it to the registry
                //
                wsprintf(FriendlyName, "ToasterDevice%02d", UINumber);
                fSuccess = SetupDiSetDeviceRegistryProperty(DeviceInfoSet, 
                             DeviceInfoData,
                             SPDRP_FRIENDLYNAME,
                             (BYTE*) &FriendlyName,
                             (lstrlen(FriendlyName)+1) * sizeof(TCHAR)
                             );
                if(!fSuccess) {
                    DbgOut("SetupDiSetDeviceRegistryProperty failed!");                   
                }
            }

            // You can use PrivateData to pass Data needed for PostProcessing
            // Context->PrivateData = Something;
            
            return ERROR_DI_POSTPROCESSING_REQUIRED; //Set for PostProcessing
        }
        else // post processing 
        {
            INFCONTEXT  InfContext;
            HINF        InfFile;

            //
            // Sample code to show how you can process a custom section
            // in your INF file.
            //
            DbgOut("DIF_INSTALLDEVICE PostProcessing");

            if (INVALID_HANDLE_VALUE == (InfFile = 
                MyOpenInfFile(DeviceInfoSet,DeviceInfoData,NULL)))
            {
                return GetLastError();
            }
            
            if (SetupFindFirstLine(InfFile, // InfHandle 
                TEXT("MySection"),
                TEXT("MySpecialFlag"),
                &InfContext))
            {
                DbgOut("DIF_INSTALLDEVICE MySpecicalFlag, Do something here!");

            }                
            
        }              
        break;
        
    case DIF_REMOVE:
        DbgOut("DIF_REMOVE");
        break;

    case DIF_SELECTDEVICE:
        DbgOut("DIF_SELECTDEVICE");
        break;
    case DIF_ASSIGNRESOURCES:
        DbgOut("DIF_ASSIGNRESOURCES");
        break;
    case DIF_PROPERTIES:
        DbgOut("DIF_PROPERTIES");
        break;
    case DIF_FIRSTTIMESETUP:
        DbgOut("DIF_FIRSTTIMESETUP");
        break;
    case DIF_FOUNDDEVICE:
        DbgOut("DIF_FOUNDDEVICE");
        break;
    case DIF_SELECTCLASSDRIVERS:
        DbgOut("DIF_SELECTCLASSDRIVERS");
        break;
    case DIF_VALIDATECLASSDRIVERS:
        DbgOut("DIF_VALIDATECLASSDRIVERS");
        break;
    case DIF_INSTALLCLASSDRIVERS:
        DbgOut("DIF_INSTALLCLASSDRIVERS");
        break;
    case DIF_CALCDISKSPACE:
        DbgOut("DIF_CALCDISKSPACE");
        break;
    case DIF_DESTROYPRIVATEDATA:
        DbgOut("DIF_DESTROYPRIVATEDATA");
        break;
    case DIF_VALIDATEDRIVER:
        DbgOut("DIF_VALIDATEDRIVER");
        break;
    case DIF_MOVEDEVICE:
        DbgOut("DIF_MOVEDEVICE");
        break;
    case DIF_DETECT:
        DbgOut("DIF_DETECT");
        break;
    case DIF_INSTALLWIZARD:
        DbgOut("DIF_INSTALLWIZARD");
        break;
    case DIF_DESTROYWIZARDDATA:
        DbgOut("DIF_DESTROYWIZARDDATA");
        break;
    case DIF_PROPERTYCHANGE:
        DbgOut("DIF_PROPERTYCHANGE");
        break;
    case DIF_ENABLECLASS:
        DbgOut("DIF_ENABLECLASS");
        break;
    case DIF_DETECTVERIFY:
        DbgOut("DIF_DETECTVERIFY");
        break;
    case DIF_INSTALLDEVICEFILES:
        DbgOut("DIF_INSTALLDEVICEFILES");
        break;
    case DIF_ALLOW_INSTALL:
        DbgOut("DIF_ALLOW_INSTALL");
        break;
    case DIF_SELECTBESTCOMPATDRV:
        DbgOut("DIF_SELECTBESTCOMPATDRV");
        break;
    case DIF_REGISTERDEVICE:
        DbgOut("DIF_REGISTERDEVICE");
        break;
    case DIF_NEWDEVICEWIZARD_PRESELECT:
        DbgOut("DIF_NEWDEVICEWIZARD_PRESELECT");
        break;
    case DIF_NEWDEVICEWIZARD_SELECT:
        DbgOut("DIF_NEWDEVICEWIZARD_SELECT");
        break;
    case DIF_NEWDEVICEWIZARD_PREANALYZE:
        DbgOut("DIF_NEWDEVICEWIZARD_PREANALYZE");
        break;
    case DIF_NEWDEVICEWIZARD_POSTANALYZE:
        DbgOut("DIF_NEWDEVICEWIZARD_POSTANALYZE");
        break;
    case DIF_NEWDEVICEWIZARD_FINISHINSTALL:
        DbgOut("DIF_NEWDEVICEWIZARD_FINISHINSTALL");
        break;
    case DIF_INSTALLINTERFACES:
        DbgOut("DIF_INSTALLINTERFACES");
        break;
    case DIF_DETECTCANCEL:
        DbgOut("DIF_DETECTCANCEL");
        break;
    case DIF_REGISTER_COINSTALLERS:
        DbgOut("DIF_REGISTER_COINSTALLERS");
        break;
    case DIF_ADDPROPERTYPAGE_ADVANCED:
        DbgOut("DIF_ADDPROPERTYPAGE_ADVANCED");
        break;
    case DIF_ADDPROPERTYPAGE_BASIC:
        DbgOut("DIF_ADDPROPERTYPAGE_BASIC");
        break;
    case DIF_TROUBLESHOOTER:
        DbgOut("DIF_TROUBLESHOOTER");
        break;
    case DIF_POWERMESSAGEWAKE:
        DbgOut("DIF_POWERMESSAGEWAKE");
        break;
    default:
        DbgOut("?????");
        break;
    }
    
    return NO_ERROR;    
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// RemoveService
//
// This function removes a service from the registry
//
DWORD RemoveService(LPCTSTR pszFilterName)
{
    DWORD status = ERROR_SUCCESS;

    SC_HANDLE schSCManager = OpenSCManager(
                                    NULL,                   // computer name
                                    NULL,                   // SCM database name
                                    SC_MANAGER_ALL_ACCESS   // access type
                                    );

    if (schSCManager)
    {
        SC_HANDLE schService = OpenService(
                                    schSCManager,       // handle to SCM database
                                    pszFilterName,      // service name
                                    SERVICE_ALL_ACCESS  // access
                                    );

        if (schService)
        {
            status = DeleteService(schService);
            CloseServiceHandle(schService);
        }
        else
        {
            status = GetLastError();
        }

        CloseServiceHandle(schSCManager);
    }
    else
    {
        status = GetLastError();
    }

    return status;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// AddService
//
// This function adds a service to the registry
//
DWORD AddService(LPCTSTR pszFilterName, LPCTSTR pszServiceBinary)
{
    DWORD status = ERROR_SUCCESS;

    SC_HANDLE schSCManager = OpenSCManager(
                                NULL,                 // computer name
                                NULL,                 // SCM database name
                                SC_MANAGER_ALL_ACCESS // access type
                                );

    if (schSCManager)
    {

        SC_HANDLE schService = CreateService(
                                    schSCManager,          // SCManager database
                                    pszFilterName,         // name of service
                                    pszFilterName,         // name to display
                                    SERVICE_ALL_ACCESS,    // desired access
                                    SERVICE_KERNEL_DRIVER, // service type
                                    SERVICE_DEMAND_START,  // start type
                                    SERVICE_ERROR_NORMAL,  // error control type
                                    pszServiceBinary,      // service's binary
                                    NULL,                  // no load ordering group
                                    NULL,                  // no tag identifier
                                    NULL,                  // no dependencies
                                    NULL,                  // LocalSystem account
                                    NULL                   // no password
                                    );
        if (schService)
        {
            CloseServiceHandle(schService);
        }
        else
        {
            status = GetLastError();
        }

        CloseServiceHandle(schSCManager);
    }
    else
    {
        status = GetLastError();
    }

    return status;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//  SearchMultiSz
//      This function searches for a substring within a string.
//
//  Arguments:
//      IN  Value
//              string to search
//
//      IN  ValueLength
//              length of the string to search
//
//      IN  SearchString
//              substring used in the search
//
//  Return Value:
//      NULL if string not found; otherwise pointer to next string character
//		just after the search string
//
LPTSTR SearchMultiSz(LPTSTR Value, ULONG ValueLength, LPCTSTR SearchString)
{
    if(ValueLength < _tcslen(SearchString)*sizeof(TCHAR))
        return NULL;

    SIZE_T length = ValueLength - _tcslen(SearchString)*sizeof(TCHAR);
    do
    {
        if (!_tcsicmp(&Value[length/sizeof(TCHAR)], SearchString))
            return &Value[length];

    }
    while(--length);

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//  Install
//      This function is exported by the dll.  The function installs
//		the WDM filter driver.
//
//  Arguments:
//      None
//
//  Return Value:
//      Status
//
DWORD Install(void)
{
    DWORD status = ERROR_SUCCESS;

    TCHAR windowsDirectory[MAX_PATH];

    ZeroMemory(windowsDirectory, sizeof(windowsDirectory));

    if (!GetWindowsDirectory(windowsDirectory, sizeof(windowsDirectory)))
    {
        status = GetLastError();
        return status;
    }

    SIZE_T newFileNameLength = _tcslen(windowsDirectory) + _tcslen(_T("\\System32\\Drivers\\")) + _tcslen(_T("SerialClone.sys")) + 1;
    LPTSTR newFileName = new TCHAR[newFileNameLength];
    if (newFileName == NULL)
    {
        status = ERROR_NOT_ENOUGH_MEMORY;
        return status;
    }

    ZeroMemory(newFileName, sizeof(newFileNameLength));

    _tcscpy(newFileName, windowsDirectory);
    _tcscat(newFileName, _T("\\System32\\Drivers\\"));
    _tcscat(newFileName, _T("SerialClone.sys"));

    // Copy the driver file to system32/drivers
    if(!CopyFile(
                _T("SerialClone.sys"),  // name of an existing file
                newFileName,                // name of new file
                FALSE                       // operation if file exists
                ))
    {
        delete newFileName;

        status = GetLastError();
        return status;
    }

    delete newFileName;

    status = AddService(_T("SerialClone"), _T("System32\\Drivers\\SerialClone.sys"));

    if ((status != ERROR_SUCCESS) && (status != ERROR_SERVICE_EXISTS))
    {
        return status;
    }

	// here we want only info about serial ports 
    HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        status = GetLastError();
        return status;
    }

    SP_DEVINFO_DATA devInfoData = {sizeof(SP_DEVINFO_DATA)};
    for (DWORD index = 0; SetupDiEnumDeviceInfo(hDevInfo, index, &devInfoData); ++index)
    {
        TCHAR devDesc[MAX_PATH];
        DWORD nSize = 0;

        if (SetupDiGetDeviceRegistryProperty(
                hDevInfo,
                &devInfoData,
                SPDRP_DEVICEDESC,
                NULL,
                (PBYTE)&devDesc,
                sizeof(devDesc),
                &nSize)
                )
        {
            if (_tcscmp(devDesc, _T("Communications Port")) == 0)
            {
                TCHAR filters[MAX_PATH];
                DWORD filtersLength = 0;

                if (SetupDiGetDeviceRegistryProperty(
                        hDevInfo,
                        &devInfoData,
                        SPDRP_UPPERFILTERS,
                        NULL,
                        (PBYTE)filters,
                        sizeof(filters),
                        &filtersLength)
                        )
                {
                    LPTSTR p = SearchMultiSz(filters, filtersLength, _T("SerialClone"));

                    if (p == NULL)
                    {
                        _tcscpy(&filters[filtersLength/sizeof(TCHAR) - 1], _T("SerialClone"));
                        filtersLength += (DWORD)_tcslen(_T("SerialClone"))*sizeof(TCHAR);
                        filters[filtersLength/sizeof(TCHAR)] = 0;
                        filters[filtersLength/sizeof(TCHAR) + 1] = 0;

                        if (!SetupDiSetDeviceRegistryProperty(
                                hDevInfo,
                                &devInfoData,
                                SPDRP_UPPERFILTERS,
                                (PBYTE)filters,
                                filtersLength + sizeof(TCHAR))
                                )
                        {
                            status = GetLastError();
                        }
                    }
                }
                else
                {
                    status = GetLastError();

                    if (status == ERROR_INVALID_DATA)
                    {
                        status = ERROR_SUCCESS;

                        _tcscpy(filters, _T("SerialClone"));
                        filtersLength = (DWORD)_tcslen(_T("SerialClone"))*sizeof(TCHAR);
                        filters[filtersLength/sizeof(TCHAR)] = 0;
                        filters[filtersLength/sizeof(TCHAR) + 1] = 0;

                        if (!SetupDiSetDeviceRegistryProperty(
                                hDevInfo,
                                &devInfoData,
                                SPDRP_UPPERFILTERS,
                                (PBYTE)filters,
                                filtersLength + 2*sizeof(TCHAR))
                                )
                        {
                            status = GetLastError();
                        }
                    }
                }
            }
        }
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);

    return status;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//  Uninstall
//      This function is exported by the dll.  The function uninstalls
//		the WDM filter driver.
//
//  Arguments:
//      None
//
//  Return Value:
//      Status
//
DWORD Uninstall(void)
{
    DWORD status = ERROR_SUCCESS;

    HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        status = GetLastError();
        return status;
    }

    SP_DEVINFO_DATA devInfoData = {sizeof(SP_DEVINFO_DATA)};
    for (DWORD index = 0; SetupDiEnumDeviceInfo(hDevInfo, index, &devInfoData); ++index)
    {
        TCHAR devDesc[MAX_PATH];
        DWORD nSize = 0;

        if (SetupDiGetDeviceRegistryProperty(
                hDevInfo,
                &devInfoData,
                SPDRP_DEVICEDESC,
                NULL,
                (PBYTE)&devDesc,
                sizeof(devDesc),
                &nSize)
                )
        {
            if (_tcscmp(devDesc, _T("Communications Port")) == 0)
            {
                TCHAR filters[MAX_PATH];
                DWORD filtersLength = 0;

                if (SetupDiGetDeviceRegistryProperty(
                        hDevInfo,
                        &devInfoData,
                        SPDRP_UPPERFILTERS,
                        NULL,
                        (PBYTE)filters,
                        sizeof(filters),
                        &filtersLength)
                        )
                {
                    LPTSTR p = SearchMultiSz(filters, filtersLength, _T("SerialClone"));

                    if (p != NULL)
                    {
                        MoveMemory(
                            p,
                            p + _tcslen(_T("SerialClone"))*sizeof(TCHAR) + sizeof(TCHAR),
                            filtersLength - (p - filters)*sizeof(TCHAR) - _tcslen(_T("SerialClone"))*sizeof(TCHAR) - sizeof(TCHAR)
                            );

                        filtersLength -= (DWORD)(_tcslen(_T("SerialClone")) + 1)*sizeof(TCHAR);

                        if (!SetupDiSetDeviceRegistryProperty(
                                hDevInfo,
                                &devInfoData,
                                SPDRP_UPPERFILTERS,
                                (PBYTE)filters,
                                filtersLength)
                                )
                        {
                            status = GetLastError();
                        }
                    }
                }
                else
                {
                    status = GetLastError();
                }
            }
        }
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);

    status = RemoveService(_T("SerialClone"));

    return status;
}
