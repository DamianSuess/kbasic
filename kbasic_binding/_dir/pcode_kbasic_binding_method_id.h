static const int pcode___dir___dir = pcode___dir * SPACE;

static const int pcode___dir__METHOD_Create = pcode___dir___dir + 1;
static const int pcode___dir__METHOD_RecursiveCreate = pcode___dir__METHOD_Create + 1;
static const int pcode___dir__METHOD_Remove = pcode___dir__METHOD_RecursiveCreate + 1;
static const int pcode___dir__METHOD_RecursiveRemove = pcode___dir__METHOD_Remove + 1;
static const int pcode___dir__METHOD_FindFile = pcode___dir__METHOD_RecursiveRemove + 1;
static const int pcode___dir__METHOD_RecursiveFindFile = pcode___dir__METHOD_FindFile + 1;
static const int pcode___dir__METHOD_FindFile1 = pcode___dir__METHOD_RecursiveFindFile + 1;
static const int pcode___dir__METHOD_RecursiveFindFile1 = pcode___dir__METHOD_FindFile1 + 1;
static const int pcode___dir__METHOD_FileList = pcode___dir__METHOD_RecursiveFindFile1 + 1;
static const int pcode___dir__METHOD_RecursiveFileList = pcode___dir__METHOD_FileList + 1;
static const int pcode___dir__METHOD_Copy = pcode___dir__METHOD_RecursiveFileList + 1;
static const int pcode___dir__METHOD_Move = pcode___dir__METHOD_Copy + 1;
static const int pcode___dir__METHOD_Exists = pcode___dir__METHOD_Move + 1;
static const int pcode___dir__METHOD_ExistsAndIsDir = pcode___dir__METHOD_Exists + 1;
static const int pcode___dir__METHOD_DateTimeCreated = pcode___dir__METHOD_ExistsAndIsDir + 1;
static const int pcode___dir__METHOD_DateTimeUpdated = pcode___dir__METHOD_DateTimeCreated + 1;
static const int pcode___dir__METHOD_DateTimeRead = pcode___dir__METHOD_DateTimeUpdated + 1;
static const int pcode___dir__METHOD_Owner = pcode___dir__METHOD_DateTimeRead + 1;
static const int pcode___dir__METHOD_Group = pcode___dir__METHOD_Owner + 1;
static const int pcode___dir__METHOD_IsReadable = pcode___dir__METHOD_Group + 1;
static const int pcode___dir__METHOD_IsWriteable = pcode___dir__METHOD_IsReadable + 1;
static const int pcode___dir__METHOD_IsExecutable = pcode___dir__METHOD_IsWriteable + 1;
static const int pcode___dir__METHOD_IsHidden = pcode___dir__METHOD_IsExecutable + 1;
static const int pcode___dir__METHOD_TempPath = pcode___dir__METHOD_IsHidden + 1;
static const int pcode___dir__METHOD_RootPath = pcode___dir__METHOD_TempPath + 1;
static const int pcode___dir__METHOD_IsDir = pcode___dir__METHOD_RootPath + 1;
static const int pcode___dir__METHOD_Drives = pcode___dir__METHOD_IsDir + 1;
static const int pcode___dir__METHOD_HomePath = pcode___dir__METHOD_Drives + 1;
static const int pcode___dir__METHOD_WithNativeSeparators = pcode___dir__METHOD_HomePath + 1;
static const int pcode___dir__METHOD_WithoutNativeSeparators = pcode___dir__METHOD_WithNativeSeparators + 1;
static const int pcode___dir__METHOD_BundleName = pcode___dir__METHOD_WithoutNativeSeparators + 1;
static const int pcode___dir__METHOD_SymLinkTarget = pcode___dir__METHOD_BundleName + 1;
static const int pcode___dir__METHOD_Name = pcode___dir__METHOD_SymLinkTarget + 1;
static const int pcode___dir__METHOD_Path = pcode___dir__METHOD_Name + 1;
static const int pcode___dir__METHOD_Suffix = pcode___dir__METHOD_Path + 1;

static const int pcode___dir__METHOD_IsRoot = pcode___dir__METHOD_Suffix + 1;
static const int pcode___dir__METHOD_IsRelative = pcode___dir__METHOD_IsRoot + 1;
static const int pcode___dir__METHOD_IsSymLink = pcode___dir__METHOD_IsRelative + 1;
static const int pcode___dir__METHOD_IsBundle = pcode___dir__METHOD_IsSymLink + 1;

