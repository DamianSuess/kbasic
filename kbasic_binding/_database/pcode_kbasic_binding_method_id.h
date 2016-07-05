
static const int pcode___database___database = pcode___database * SPACE;

static const int pcode___database__METHOD_Exists = pcode___database___database + 1;
static const int pcode___database__METHOD_SetCurrentDatabase = pcode___database__METHOD_Exists + 1;
static const int pcode___database__METHOD_CurrentDatabase = pcode___database__METHOD_SetCurrentDatabase + 1;
static const int pcode___database__METHOD_OpenSQLite = pcode___database__METHOD_CurrentDatabase + 1;
static const int pcode___database__METHOD_Open = pcode___database__METHOD_OpenSQLite + 1;
static const int pcode___database__METHOD_Open1 = pcode___database__METHOD_Open + 1;
static const int pcode___database__METHOD_Close = pcode___database__METHOD_Open1 + 1;
static const int pcode___database__METHOD_IsOpen = pcode___database__METHOD_Close + 1;
static const int pcode___database__METHOD_Create = pcode___database__METHOD_IsOpen + 1;
static const int pcode___database__METHOD_TestConnection = pcode___database__METHOD_Create + 1;
static const int pcode___database__METHOD_Clear = pcode___database__METHOD_TestConnection + 1;
static const int pcode___database__METHOD_Drop = pcode___database__METHOD_Clear + 1;
static const int pcode___database__METHOD_Copy = pcode___database__METHOD_Drop + 1;
static const int pcode___database__METHOD_LastSQLError = pcode___database__METHOD_Copy + 1;
static const int pcode___database__METHOD_LastSQLCommands = pcode___database__METHOD_LastSQLError + 1;
static const int pcode___database__METHOD_LastSQLCommandFailed = pcode___database__METHOD_LastSQLCommands + 1;
//static const int pcode___database__METHOD_LastErrorText = pcode___database__METHOD_LastSQLError + 1;

static const int pcode___database__METHOD_IsTransactionSupported = pcode___database__METHOD_LastSQLCommandFailed + 1;
static const int pcode___database__METHOD_Transaction = pcode___database__METHOD_IsTransactionSupported + 1;
static const int pcode___database__METHOD_Commit = pcode___database__METHOD_Transaction + 1;
static const int pcode___database__METHOD_Rollback = pcode___database__METHOD_Commit + 1;

static const int pcode___database__METHOD_Tables = pcode___database__METHOD_Rollback + 1;
static const int pcode___database__METHOD_Drivers = pcode___database__METHOD_Tables + 1;

static const int pcode___database__METHOD_MySQL = pcode___database__METHOD_Drivers + 1;
static const int pcode___database__METHOD_PostgreSQL = pcode___database__METHOD_MySQL + 1;
static const int pcode___database__METHOD_SQLite = pcode___database__METHOD_PostgreSQL + 1;
static const int pcode___database__METHOD_ODBC = pcode___database__METHOD_SQLite + 1;
static const int pcode___database__METHOD_LocalHost = pcode___database__METHOD_ODBC + 1;
static const int pcode___database__METHOD_DefaultPort = pcode___database__METHOD_LocalHost + 1;
static const int pcode___database__METHOD_DefaultOptions = pcode___database__METHOD_DefaultPort + 1;

