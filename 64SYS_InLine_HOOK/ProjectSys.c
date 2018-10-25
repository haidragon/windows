#include "ProjectSys.h"
#include "HookApi.h"

HANDLE MyPid=0;
PVOID obHandle;
PMDL m_MDL;
PVOID *m_Mapped;


PHOOKENVIRONMENT ZwOpenPro=NULL;//函数地址;


NTSYSAPI NTSTATUS NTAPI ZwOpenProcess(OUT PHANDLE ProcessHandle,IN ACCESS_MASK DesiredAccess,IN POBJECT_ATTRIBUTES ObjectAttributes,IN PCLIENT_ID ClientId OPTIONAL);


typedef NTSTATUS (__stdcall *_NTOpenProcess)(PHANDLE  ProcessHandle,
	ACCESS_MASK        DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PCLIENT_ID         ClientId
	);


NTSTATUS MyOpenProcess( PHANDLE    ProcessHandle, ACCESS_MASK  DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID   ClientId)
{
	if (ClientId->UniqueProcess == MyPid)
	{
		return STATUS_ACCESS_DENIED;
	}	
	return ((_NTOpenProcess)(ZwOpenPro))(ProcessHandle,DesiredAccess,ObjectAttributes,ClientId);
}



NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObj, IN PUNICODE_STRING pRegistryString)
{
	NTSTATUS		status = STATUS_SUCCESS;
	UNICODE_STRING  ustrLinkName;
	UNICODE_STRING  ustrDevName;  
	PDEVICE_OBJECT  pDevObj;

	pDriverObj->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	pDriverObj->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	pDriverObj->DriverUnload = DriverUnload;

	//SetFlagForceIntegrity(pDriverObj);//签名验证;
#ifdef _WIN64
	LDE_init();
#endif

	ZwOpenPro = InstallHookApi(L"NtOpenProcess",MyOpenProcess);


	RtlInitUnicodeString(&ustrDevName, DEVICE_NAME);
	status = IoCreateDevice(pDriverObj, 
				0,
				&ustrDevName, 
				FILE_DEVICE_UNKNOWN,
				0,
				FALSE,
				&pDevObj);

	if(!NT_SUCCESS(status))
	{
		dprintf("[ProjectSys] Error, IoCreateDevice = 0x%x\r\n", status);
		return status;
	}


	if(IoIsWdmVersionAvailable(1,0x10))
	{
		RtlInitUnicodeString(&ustrLinkName, SYMBOLIC_LINK_GLOBAL_NAME);
	}
	else
	{
		RtlInitUnicodeString(&ustrLinkName, SYMBOLIC_LINK_NAME);
	}
	

	status = IoCreateSymbolicLink(&ustrLinkName, &ustrDevName);  
	
	if(!NT_SUCCESS(status))
	{
		dprintf("[ProjectSys] Error, IoCreateSymbolicLink = 0x%x\r\n", status);
		
		IoDeleteDevice(pDevObj); 
		return status;
	}	



	dprintf("[ProjectSys] DriverEntry Success\r\n");
	return STATUS_SUCCESS;
}

VOID DriverUnload(IN PDRIVER_OBJECT pDriverObj)
{	
	UNICODE_STRING strLink;
	dprintf("[ProjectSys] Unloading...\r\n");;	

	RtlInitUnicodeString(&strLink, SYMBOLIC_LINK_NAME);
	IoDeleteSymbolicLink(&strLink);
	IoDeleteDevice(pDriverObj->DeviceObject);
	
	UnInstallHookApi(ZwOpenPro);

#ifdef _WIN64
	ExFreePool(LDE);
#endif

	dprintf("[ProjectSys] Unloaded Success\r\n");
	return;
}

NTSTATUS DispatchCreate(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;

	MyPid =PsGetCurrentProcessId();
	dprintf("[ProjectSys] IRP_MJ_CREATE\r\n");

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}


NTSTATUS DispatchClose(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

