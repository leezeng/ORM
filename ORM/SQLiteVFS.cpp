
#include "SQLiteVFS.h"
#include <vector>
CAbstractVFS::CAbstractVFS()
{
	xOpen = __xOpen;
	xDelete = __xDelete;
	xAccess = __xAccess;
	xFullPathname = __xFullPathname;
	xDlOpen = __xDlOpen;
	xDlError = __xDlError;
	xDlSym = __xDlSym;
	xDlClose = __xDlClose;
	xRandomness = __xRandomness;
	xSleep = __xSleep;
	xCurrentTime = __xCurrentTime;
	xGetLastError = __xGetLastError;
	xCurrentTimeInt64 = __xCurrentTimeInt64;
	xSetSystemCall = __xSetSystemCall;
	xGetSystemCall = __xGetSystemCall;
	xNextSystemCall = __xNextSystemCall;
}

CAbstractVFS::~CAbstractVFS()
{
}

int CAbstractVFS::__xOpen(sqlite3_vfs *vfs, const char *zName, sqlite3_file *pFile, int flags, int *pOutFlags)
{
	return static_cast<CAbstractVFS*>(vfs)->Open(zName, pFile, flags, pOutFlags);
}

int CAbstractVFS::__xDelete(sqlite3_vfs *vfs, const char *zName, int syncDir)
{
	return static_cast<CAbstractVFS*>(vfs)->Delete(zName, syncDir);
}

int CAbstractVFS::__xAccess(sqlite3_vfs *vfs, const char *zName, int flags, int *pResOut)
{
	return static_cast<CAbstractVFS*>(vfs)->Access(zName, flags, pResOut);
}

int CAbstractVFS::__xFullPathname(sqlite3_vfs *vfs, const char *zName, int nOut, char *zOut)
{
	return static_cast<CAbstractVFS*>(vfs)->FullPathname(zName, nOut, zOut);
}

void *CAbstractVFS::__xDlOpen(sqlite3_vfs *vfs, const char *zFilename)
{
	return static_cast<CAbstractVFS*>(vfs)->DlOpen(zFilename);
}

void CAbstractVFS::__xDlError(sqlite3_vfs *vfs, int nByte, char *zErrMsg)
{
	return static_cast<CAbstractVFS*>(vfs)->DlError(nByte, zErrMsg);
}

void (*CAbstractVFS::__xDlSym(sqlite3_vfs *vfs, void *pModule, const char *zSymbol))(void)
{
	return static_cast<CAbstractVFS*>(vfs)->DlSym(pModule, zSymbol);
}

void CAbstractVFS::__xDlClose(sqlite3_vfs *vfs, void *pModule)
{
	return static_cast<CAbstractVFS*>(vfs)->DlClose(pModule);
}

int CAbstractVFS::__xRandomness(sqlite3_vfs *vfs, int nByte, char *zOut)
{
	return static_cast<CAbstractVFS*>(vfs)->Randomness(nByte, zOut);
}

int CAbstractVFS::__xSleep(sqlite3_vfs *vfs, int microseconds)
{
	return static_cast<CAbstractVFS*>(vfs)->Sleep(microseconds);
}

int CAbstractVFS::__xCurrentTime(sqlite3_vfs *vfs, double *t)
{
	return static_cast<CAbstractVFS*>(vfs)->CurrentTime(t);
}

int CAbstractVFS::__xGetLastError(sqlite3_vfs *vfs, int n, char *p)
{
	return static_cast<CAbstractVFS*>(vfs)->GetLastError(n, p);
}

int CAbstractVFS::__xCurrentTimeInt64(sqlite3_vfs *vfs, sqlite3_int64 *t)
{
	return static_cast<CAbstractVFS*>(vfs)->CurrentTimeInt64(t);
}

int CAbstractVFS::__xSetSystemCall(sqlite3_vfs *vfs, const char *zName, sqlite3_syscall_ptr p)
{
	return static_cast<CAbstractVFS*>(vfs)->SetSystemCall(zName, p);
}

sqlite3_syscall_ptr CAbstractVFS::__xGetSystemCall(sqlite3_vfs *vfs, const char *zName)
{
	return static_cast<CAbstractVFS*>(vfs)->GetSystemCall(zName);
}

const char *CAbstractVFS::__xNextSystemCall(sqlite3_vfs *vfs, const char *zName)
{
	return static_cast<CAbstractVFS*>(vfs)->NextSystemCall(zName);
}

//---------------------------------------------------------------------------
//
// CDelegateVFS
//
//---------------------------------------------------------------------------

CDelegateVFS::CDelegateVFS()
	: m_pDelegate(nullptr)
{
}

CDelegateVFS::~CDelegateVFS()
{
}

void CDelegateVFS::SetDelegate(sqlite3_vfs *pDelegate)
{
	m_pDelegate = pDelegate;
}

sqlite3_vfs *CDelegateVFS::GetDelegate() const
{
	return m_pDelegate;
}

int CDelegateVFS::Open(const char *zName, sqlite3_file *pFile, int flags, int *pOutFlags)
{
	return m_pDelegate->xOpen(m_pDelegate, zName, pFile, flags, pOutFlags);
}

int CDelegateVFS::Delete(const char *zName, int syncDir)
{
	return m_pDelegate->xDelete(m_pDelegate, zName, syncDir);
}

int CDelegateVFS::Access(const char *zName, int flags, int *pResOut)
{
	return m_pDelegate->xAccess(m_pDelegate, zName, flags, pResOut);
}

int CDelegateVFS::FullPathname(const char *zName, int nOut, char *zOut)
{
	return m_pDelegate->xFullPathname(m_pDelegate, zName, nOut, zOut);
}

void *CDelegateVFS::DlOpen(const char *zFilename)
{
	return m_pDelegate->xDlOpen(m_pDelegate, zFilename);
}

void CDelegateVFS::DlError(int nByte, char *zErrMsg)
{
	return m_pDelegate->xDlError(m_pDelegate, nByte, zErrMsg);
}

void (*CDelegateVFS::DlSym(void *pModule, const char *zSymbol))(void)
{
	return m_pDelegate->xDlSym(m_pDelegate, pModule, zSymbol);
}

void CDelegateVFS::DlClose(void *pModule)
{
	return m_pDelegate->xDlClose(m_pDelegate, pModule);
}

int CDelegateVFS::Randomness(int nByte, char *zOut)
{
	return m_pDelegate->xRandomness(m_pDelegate, nByte, zOut);
}

int CDelegateVFS::Sleep(int microseconds)
{
	return m_pDelegate->xSleep(m_pDelegate, microseconds);
}

int CDelegateVFS::CurrentTime(double *t)
{
	return m_pDelegate->xCurrentTime(m_pDelegate, t);
}

int CDelegateVFS::GetLastError(int n, char *p)
{
	return m_pDelegate->xGetLastError(m_pDelegate, n, p);
}

int CDelegateVFS::CurrentTimeInt64(sqlite3_int64 *t)
{
	return m_pDelegate->xCurrentTimeInt64(m_pDelegate, t);
}

int CDelegateVFS::SetSystemCall(const char *zName, sqlite3_syscall_ptr p)
{
	return m_pDelegate->xSetSystemCall(m_pDelegate, zName, p);
}

sqlite3_syscall_ptr CDelegateVFS::GetSystemCall(const char *zName)
{
	return m_pDelegate->xGetSystemCall(m_pDelegate, zName);
}

const char *CDelegateVFS::NextSystemCall(const char *zName)
{
	return m_pDelegate->xNextSystemCall(m_pDelegate, zName);
}


//---------------------------------------------------------------------------
//
// CSimpleEncryptedVFS
//
//---------------------------------------------------------------------------

const sqlite3_io_methods CSimpleEncryptedVFS::s_methods =
{
	2,
	&CSimpleEncryptedVFS::__Close,
	&CSimpleEncryptedVFS::__Read,
	&CSimpleEncryptedVFS::__Write,
	&CSimpleEncryptedVFS::__Truncate,
	&CSimpleEncryptedVFS::__Sync,
	&CSimpleEncryptedVFS::__FileSize,
	&CSimpleEncryptedVFS::__Lock,
	&CSimpleEncryptedVFS::__Unlock,
	&CSimpleEncryptedVFS::__CheckReservedLock,
	&CSimpleEncryptedVFS::__FileControl,
	&CSimpleEncryptedVFS::__SectorSize,
	&CSimpleEncryptedVFS::__DeviceCharacteristics,
	&CSimpleEncryptedVFS::__ShmMap,
	&CSimpleEncryptedVFS::__ShmLock,
	&CSimpleEncryptedVFS::__ShmBarrier,
	&CSimpleEncryptedVFS::__ShmUnmap,
//	&CSimpleEncryptedVFS::__Fetch,
//	&CSimpleEncryptedVFS::__Unfetch
};

CSimpleEncryptedVFS::CSimpleEncryptedVFS()
{
}

CSimpleEncryptedVFS::~CSimpleEncryptedVFS()
{
}

bool CSimpleEncryptedVFS::Setup()
{
	if (GetDelegate() != nullptr)
	{
		return true;
	}

	sqlite3_vfs *vfs = sqlite3_vfs_find("win32");
	if (vfs == nullptr)
	{
		return false;
	}

	iVersion = vfs->iVersion;
	szOsFile = sizeof(FileInfo) + vfs->szOsFile - sizeof(sqlite3_file);
	mxPathname = vfs->mxPathname;
	pNext = nullptr;
	zName = "CSimpleEncryptedVFS";
	pAppData = nullptr;

	if (SQLITE_OK != sqlite3_vfs_register(this, 1))
	{
		return false;
	}

	SetDelegate(vfs);
	return true;
}

int CSimpleEncryptedVFS::Open(const char *zName, sqlite3_file *pFile, int flags, int *pOutFlags)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	pFileInfo->flags = flags;
	pFileInfo->pMethods = &s_methods;
	int r = CDelegateVFS::Open(zName, &pFileInfo->f, flags, pOutFlags);
	if (r != SQLITE_OK)
	{
		pFileInfo->f.pMethods = nullptr;
	}

	return r;
}

int CSimpleEncryptedVFS::__Close(sqlite3_file *pFile)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	if (pFileInfo->f.pMethods == nullptr)
	{
		return SQLITE_OK;
	}

	if (pFileInfo->f.pMethods->xClose == nullptr)
	{
		return SQLITE_OK;
	}

	return pFileInfo->f.pMethods->xClose(&pFileInfo->f);
}

int CSimpleEncryptedVFS::__Read(sqlite3_file *pFile, void *p, int iAmt, sqlite3_int64 iOfst)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);

	int r;

	if ((pFileInfo->flags & SQLITE_OPEN_MAIN_DB) != 0 && iOfst == 0)
	{
		char *p1 = static_cast<char*>(p);
		char buff[512];

		int iCount = iAmt;

		if (iCount < 512)
		{
			iCount = 512;
			p1 = buff;
			memcpy(p1, p, iAmt);
		}

		r = pFileInfo->f.pMethods->xRead(&pFileInfo->f, p1, iCount, iOfst);

		if (r == SQLITE_OK)
		{
			//DecodeBlock(p1);
		}

		if (p1 != p)
		{
			memcpy(p, p1, iAmt);
		}

		return r;
	}

	return pFileInfo->f.pMethods->xRead(&pFileInfo->f, p, iAmt, iOfst);
}

int CSimpleEncryptedVFS::__Write(sqlite3_file *pFile, const void *p, int iAmt, sqlite3_int64 iOfst)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);

	if ((pFileInfo->flags & SQLITE_OPEN_MAIN_DB) != 0 && iOfst == 0 && iAmt >= 512)
	{
		std::vector<char> buff(iAmt);
		memcpy(buff.data(), p, iAmt);
		//EncodeBlock(buff.data());
		return pFileInfo->f.pMethods->xWrite(&pFileInfo->f, buff.data(), iAmt, iOfst);
	}

	return pFileInfo->f.pMethods->xWrite(&pFileInfo->f, p, iAmt, iOfst);
}

int CSimpleEncryptedVFS::__Truncate(sqlite3_file *pFile, sqlite3_int64 size)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xTruncate(&pFileInfo->f, size);
}

int CSimpleEncryptedVFS::__Sync(sqlite3_file *pFile, int flags)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xSync(&pFileInfo->f, flags);
}

int CSimpleEncryptedVFS::__FileSize(sqlite3_file *pFile, sqlite3_int64 *pSize)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xFileSize(&pFileInfo->f, pSize);
}

int CSimpleEncryptedVFS::__Lock(sqlite3_file *pFile, int n)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xLock(&pFileInfo->f, n);
}

int CSimpleEncryptedVFS::__Unlock(sqlite3_file *pFile, int n)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xUnlock(&pFileInfo->f, n);
}

int CSimpleEncryptedVFS::__CheckReservedLock(sqlite3_file *pFile, int *pResOut)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xCheckReservedLock(&pFileInfo->f, pResOut);
}

int CSimpleEncryptedVFS::__FileControl(sqlite3_file *pFile, int op, void *pArg)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xFileControl(&pFileInfo->f, op, pArg);
}

int CSimpleEncryptedVFS::__SectorSize(sqlite3_file *pFile)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xSectorSize(&pFileInfo->f);
}

int CSimpleEncryptedVFS::__DeviceCharacteristics(sqlite3_file *pFile)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xDeviceCharacteristics(&pFileInfo->f);
}

int CSimpleEncryptedVFS::__ShmMap(sqlite3_file *pFile, int iPg, int pgsz, int n, void volatile **pp)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xShmMap(&pFileInfo->f, iPg, pgsz, n, pp);
}

int CSimpleEncryptedVFS::__ShmLock(sqlite3_file *pFile, int offset, int n, int flags)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xShmLock(&pFileInfo->f, offset, n, flags);
}

void CSimpleEncryptedVFS::__ShmBarrier(sqlite3_file *pFile)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xShmBarrier(&pFileInfo->f);
}

int CSimpleEncryptedVFS::__ShmUnmap(sqlite3_file *pFile, int deleteFlag)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xShmUnmap(&pFileInfo->f, deleteFlag);
}
/*
int CSimpleEncryptedVFS::__Fetch(sqlite3_file *pFile, sqlite3_int64 iOfst, int iAmt, void **pp)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xFetch(&pFileInfo->f, iOfst, iAmt, pp);
}

int CSimpleEncryptedVFS::__Unfetch(sqlite3_file *pFile, sqlite3_int64 iOfst, void *p)
{
	FileInfo *pFileInfo = reinterpret_cast<FileInfo*>(pFile);
	return pFileInfo->f.pMethods->xUnfetch(&pFileInfo->f, iOfst, p);
}
*/ 

std::shared_ptr<CSimpleEncryptedVFS> g_vfs;

void SivInstallSQLiteVFS()
{

	if (g_vfs == nullptr)
	{
		g_vfs = std::make_shared<CSimpleEncryptedVFS>();
		g_vfs->Setup();
	}
}
