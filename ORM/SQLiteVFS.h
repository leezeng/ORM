


#ifndef __SQLiteVFS_h__
#define __SQLiteVFS_h__

#include "sqlite3.h"


class CAbstractVFS
	: public sqlite3_vfs
{
public:
	virtual ~CAbstractVFS();

protected:
	CAbstractVFS();

	virtual int Open(const char *zName, sqlite3_file *pFile, int flags, int *pOutFlags) = 0;
	virtual int Delete(const char *zName, int syncDir) = 0;
	virtual int Access(const char *zName, int flags, int *pResOut) = 0;
	virtual int FullPathname(const char *zName, int nOut, char *zOut) = 0;
	virtual void *DlOpen(const char *zFilename) = 0;
	virtual void DlError(int nByte, char *zErrMsg) = 0;
	virtual void (*DlSym(void *pModule, const char *zSymbol))(void) = 0;
	virtual void DlClose(void *pModule) = 0;
	virtual int Randomness(int nByte, char *zOut) = 0;
	virtual int Sleep(int microseconds) = 0;
	virtual int CurrentTime(double *t) = 0;
	virtual int GetLastError(int n, char *p) = 0;
	virtual int CurrentTimeInt64(sqlite3_int64 *t) = 0;
	virtual int SetSystemCall(const char *zName, sqlite3_syscall_ptr p) = 0;
	virtual sqlite3_syscall_ptr GetSystemCall(const char *zName) = 0;
	virtual const char *NextSystemCall(const char *zName) = 0;

private:
	static int __xOpen(sqlite3_vfs *vfs, const char *zName, sqlite3_file *pFile, int flags, int *pOutFlags);
	static int __xDelete(sqlite3_vfs *vfs, const char *zName, int syncDir);
	static int __xAccess(sqlite3_vfs *vfs, const char *zName, int flags, int *pResOut);
	static int __xFullPathname(sqlite3_vfs *vfs, const char *zName, int nOut, char *zOut);
	static void *__xDlOpen(sqlite3_vfs *vfs, const char *zFilename);
	static void __xDlError(sqlite3_vfs *vfs, int nByte, char *zErrMsg);
	static void (*__xDlSym(sqlite3_vfs *vfs,void *pModule, const char *zSymbol))(void);
	static void __xDlClose(sqlite3_vfs *vfs, void *pModule);
	static int __xRandomness(sqlite3_vfs *vfs, int nByte, char *zOut);
	static int __xSleep(sqlite3_vfs *vfs, int microseconds);
	static int __xCurrentTime(sqlite3_vfs *vfs, double *t);
	static int __xGetLastError(sqlite3_vfs *vfs, int n, char *p);
	static int __xCurrentTimeInt64(sqlite3_vfs *vfs, sqlite3_int64 *t);
	static int __xSetSystemCall(sqlite3_vfs *vfs, const char *zName, sqlite3_syscall_ptr p);
	static sqlite3_syscall_ptr __xGetSystemCall(sqlite3_vfs *vfs, const char *zName);
	static const char *__xNextSystemCall(sqlite3_vfs *vfs, const char *zName);
};

class CDelegateVFS
	: public CAbstractVFS
{
public:
	CDelegateVFS();
	virtual ~CDelegateVFS();

	void SetDelegate(sqlite3_vfs *pDelegate);
	sqlite3_vfs *GetDelegate() const;

	virtual int Open(const char *zName, sqlite3_file *pFile, int flags, int *pOutFlags);
	virtual int Delete(const char *zName, int syncDir);
	virtual int Access(const char *zName, int flags, int *pResOut);
	virtual int FullPathname(const char *zName, int nOut, char *zOut);
	virtual void *DlOpen(const char *zFilename);
	virtual void DlError(int nByte, char *zErrMsg);
	virtual void (*DlSym(void *pModule, const char *zSymbol))(void);
	virtual void DlClose(void *pModule);
	virtual int Randomness(int nByte, char *zOut);
	virtual int Sleep(int microseconds);
	virtual int CurrentTime(double *t);
	virtual int GetLastError(int n, char *p);
	virtual int CurrentTimeInt64(sqlite3_int64 *t);
	virtual int SetSystemCall(const char *zName, sqlite3_syscall_ptr p);
	virtual sqlite3_syscall_ptr GetSystemCall(const char *zName);
	virtual const char *NextSystemCall(const char *zName);

private:
	sqlite3_vfs *m_pDelegate;
};


class CSimpleEncryptedVFS
	: public CDelegateVFS
{
public:
	CSimpleEncryptedVFS();
	virtual ~CSimpleEncryptedVFS();

	bool Setup();

protected:
	virtual int Open(const char *zName, sqlite3_file *pFile, int flags, int *pOutFlags);

private:
	static int __Close(sqlite3_file *pFile);
	static int __Read(sqlite3_file *pFile, void *p, int iAmt, sqlite3_int64 iOfst);
	static int __Write(sqlite3_file *pFile, const void *p, int iAmt, sqlite3_int64 iOfst);
	static int __Truncate(sqlite3_file *pFile, sqlite3_int64 size);
	static int __Sync(sqlite3_file *pFile, int flags);
	static int __FileSize(sqlite3_file *pFile, sqlite3_int64 *pSize);
	static int __Lock(sqlite3_file *pFile, int n);
	static int __Unlock(sqlite3_file *pFile, int n);
	static int __CheckReservedLock(sqlite3_file *pFile, int *pResOut);
	static int __FileControl(sqlite3_file *pFile, int op, void *pArg);
	static int __SectorSize(sqlite3_file *pFile);
	static int __DeviceCharacteristics(sqlite3_file *pFile);
	static int __ShmMap(sqlite3_file *pFile, int iPg, int pgsz, int n, void volatile **pp);
	static int __ShmLock(sqlite3_file *pFile, int offset, int n, int flags);
	static void __ShmBarrier(sqlite3_file *pFile);
	static int __ShmUnmap(sqlite3_file *pFile, int deleteFlag);
	static int __Fetch(sqlite3_file *pFile, sqlite3_int64 iOfst, int iAmt, void **pp);
	static int __Unfetch(sqlite3_file *pFile, sqlite3_int64 iOfst, void *p);

	struct FileInfo
	{
		const sqlite3_io_methods *pMethods;
		int flags;
		sqlite3_file f;
	};

	static const sqlite3_io_methods s_methods;
};

#endif // __SQLiteVFS_h__
