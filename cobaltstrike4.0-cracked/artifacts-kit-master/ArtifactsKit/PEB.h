//always declare 64-bit types
#ifdef _MSC_VER
    //Visual C++
typedef unsigned __int64    QWORD;
typedef __int64             INT64;
#else
    //GCC
typedef unsigned long long  QWORD;
typedef long long           INT64;
#endif
typedef QWORD                   PTR64;
typedef QWORD                   HANDLE64;

//UNCOMMENT line below if you are not including windows.h
//#define WANT_ALL_WINDOWS_H_DEFINITIONS
#ifdef WANT_ALL_WINDOWS_H_DEFINITIONS

//base types
typedef unsigned char           BYTE;
typedef char                    CHAR;
typedef unsigned short          WORD;
typedef short                   INT16;
typedef unsigned long           DWORD;
typedef long                    INT32;
typedef unsigned __int64        QWORD;
typedef __int64                 INT64;
typedef void* HANDLE;
typedef unsigned short          WCHAR;

//base structures
union LARGE_INTEGER
{
    struct
    {
        DWORD   LowPart;
        INT32   HighPart;
    } u;
    INT64       QuadPart;
};

union ULARGE_INTEGER
{
    struct
    {
        DWORD LowPart;
        DWORD HighPart;
    } u;
    QWORD       QuadPart;
};

#endif //#ifdef WANT_ALL_WINDOWS_H_DEFINITIONS

struct UNICODE_STRING64
{
    union
    {
        struct
        {
            WORD Length;
            WORD MaximumLength;
        } u;
        QWORD dummyalign;
    };
    QWORD Buffer;
};

typedef struct _CLIENT_ID64
{
    QWORD  ProcessId;
    QWORD  ThreadId;
} CLIENT_ID64;


//NOTE: the members of this structure are not yet complete
typedef struct _RTL_USER_PROCESS_PARAMETERS64
{
    BYTE                    Reserved1[16];                 //0x00
    QWORD                   Reserved2[5];                  //0x10
    UNICODE_STRING64        CurrentDirectoryPath;          //0x38
    HANDLE64                CurrentDirectoryHandle;        //0x48
    UNICODE_STRING64        DllPath;                       //0x50 
    UNICODE_STRING64        ImagePathName;                 //0x60 
    UNICODE_STRING64        CommandLine;                   //0x70 
    PTR64                   Environment;                   //0x80
} RTL_USER_PROCESS_PARAMETERS64;

//
// PEB64 structure - TODO: comb more through http://terminus.rewolf.pl/terminus/structures/ntdll/_PEB_x64.html and add OS delineations and Windows 10 updates
//
// The structure represented here is a work-in-progress as only members thru offset 0x320 are listed; the actual sizes per OS are:
//    0x0358    XP/WS03
//    0x0368    Vista
//    0x037C    Windows 7
//    0x0388    Windows 8
//    0x07A0    Windows 10
//
struct PEB64
{
    union
    {
        struct
        {
            BYTE InheritedAddressSpace;                                 //0x000
            BYTE ReadImageFileExecOptions;                              //0x001
            BYTE BeingDebugged;                                         //0x002
            BYTE _SYSTEM_DEPENDENT_01;                                  //0x003
        } flags;
        QWORD dummyalign;
    } dword0;
    QWORD                           Mutant;                             //0x0008
    QWORD                           ImageBaseAddress;                   //0x0010
    PTR64                           Ldr;                                //0x0018
    PTR64                           ProcessParameters;                  //0x0020 / pointer to RTL_USER_PROCESS_PARAMETERS64
    QWORD                           SubSystemData;                      //0x0028
    QWORD                           ProcessHeap;                        //0x0030
    QWORD                           FastPebLock;                        //0x0038
    QWORD                           _SYSTEM_DEPENDENT_02;               //0x0040
    QWORD                           _SYSTEM_DEPENDENT_03;               //0x0048
    QWORD                           _SYSTEM_DEPENDENT_04;               //0x0050
    union
    {
        QWORD                       KernelCallbackTable;                //0x0058
        QWORD                       UserSharedInfoPtr;                  //0x0058
    };
    DWORD                           SystemReserved;                     //0x0060
    DWORD                           _SYSTEM_DEPENDENT_05;               //0x0064
    QWORD                           _SYSTEM_DEPENDENT_06;               //0x0068
    QWORD                           TlsExpansionCounter;                //0x0070
    QWORD                           TlsBitmap;                          //0x0078
    DWORD                           TlsBitmapBits[2];                   //0x0080
    QWORD                           ReadOnlySharedMemoryBase;           //0x0088
    QWORD                           _SYSTEM_DEPENDENT_07;               //0x0090
    QWORD                           ReadOnlyStaticServerData;           //0x0098
    QWORD                           AnsiCodePageData;                   //0x00A0
    QWORD                           OemCodePageData;                    //0x00A8
    QWORD                           UnicodeCaseTableData;               //0x00B0
    DWORD                           NumberOfProcessors;                 //0x00B8
    union
    {
        DWORD                       NtGlobalFlag;                       //0x00BC
        DWORD                       dummy02;                            //0x00BC
    };
    LARGE_INTEGER                   CriticalSectionTimeout;             //0x00C0
    QWORD                           HeapSegmentReserve;                 //0x00C8
    QWORD                           HeapSegmentCommit;                  //0x00D0
    QWORD                           HeapDeCommitTotalFreeThreshold;     //0x00D8
    QWORD                           HeapDeCommitFreeBlockThreshold;     //0x00E0
    DWORD                           NumberOfHeaps;                      //0x00E8
    DWORD                           MaximumNumberOfHeaps;               //0x00EC
    QWORD                           ProcessHeaps;                       //0x00F0
    QWORD                           GdiSharedHandleTable;               //0x00F8
    QWORD                           ProcessStarterHelper;               //0x0100
    QWORD                           GdiDCAttributeList;                 //0x0108
    QWORD                           LoaderLock;                         //0x0110
    DWORD                           OSMajorVersion;                     //0x0118
    DWORD                           OSMinorVersion;                     //0x011C
    WORD                            OSBuildNumber;                      //0x0120
    WORD                            OSCSDVersion;                       //0x0122
    DWORD                           OSPlatformId;                       //0x0124
    DWORD                           ImageSubsystem;                     //0x0128
    DWORD                           ImageSubsystemMajorVersion;         //0x012C
    QWORD                           ImageSubsystemMinorVersion;         //0x0130
    union
    {
        QWORD                       ImageProcessAffinityMask;           //0x0138
        QWORD                       ActiveProcessAffinityMask;          //0x0138
    };
    QWORD                           GdiHandleBuffer[30];                //0x0140
    QWORD                           PostProcessInitRoutine;             //0x0230
    QWORD                           TlsExpansionBitmap;                 //0x0238
    DWORD                           TlsExpansionBitmapBits[32];         //0x0240
    QWORD                           SessionId;                          //0x02C0
    ULARGE_INTEGER                  AppCompatFlags;                     //0x02C8
    ULARGE_INTEGER                  AppCompatFlagsUser;                 //0x02D0
    QWORD                           pShimData;                          //0x02D8
    QWORD                           AppCompatInfo;                      //0x02E0
    UNICODE_STRING64                CSDVersion;                         //0x02E8
    QWORD                           ActivationContextData;              //0x02F8
    QWORD                           ProcessAssemblyStorageMap;          //0x0300
    QWORD                           SystemDefaultActivationContextData; //0x0308
    QWORD                           SystemAssemblyStorageMap;           //0x0310
    QWORD                           MinimumStackCommit;                 //0x0318

}; //struct PEB64

//
// TEB64 structure - preliminary structure; the portion listed current at least as of Windows 8
//
struct TEB64
{
    void* ExceptionList;                              //0x0000 / Current Structured Exception Handling (SEH) frame
    void* StackBase;
    //uint32_t StackBase;                                  //0x0004 / Bottom of stack (high address)
    //uint32_t StackLimit;                                 //0x0008 / Ceiling of stack (low address)
    /*
    BYTE                            NtTib[56];                          //0x0000 / NT_TIB64 structure
    PTR64                           EnvironmentPointer;                 //0x0038
    CLIENT_ID64                     ClientId;                           //0x0040
    PTR64                           ActiveRpcHandle;                    //0x0050
    PTR64                           ThreadLocalStoragePointer;          //0x0058
    PTR64                           ProcessEnvironmentBlock;            //0x0060 / ptr to PEB64
    DWORD                           LastErrorValue;                     //0x0068
    DWORD                           CountOfOwnedCriticalSections;       //0x006C
    PTR64                           CsrClientThread;                    //0x0070
    PTR64                           Win32ThreadInfo;                    //0x0078
    DWORD                           User32Reserved[26];                 //0x0080
    DWORD                           UserReserved[6];                    //0x00E8
    PTR64                           WOW32Reserved;                      //0x0100
    DWORD                           CurrentLocale;                      //0x0108
    DWORD                           FpSoftwareStatusRegister;           //0x010C
    PTR64                           SystemReserved1[54];                //0x0110
    DWORD                           ExceptionCode;                      //0x02C0
    PTR64                           ActivationContextStackPointer;      //0x02C8
    */

}; //struct TEB64


//
// [TEB/PEB/SEH SUMMARY]
// This file contains the undocumented TEB (Thread Environment Block) and PEB (Process Environment Block)
// definitions for the Intel x86 32-bit Windows operating systems starting from NT 3.51 through Windows 10.  The TEB
// is also known as the TIB (Thread Information Block), especially under the Windows 9.x operating systems.
//
// Additionally I have added the definitions for the partially documented Win32 SEH (Structured Exception Handling)
// that are not only referenced by the TEB, but are normally strewn across both C headers and assembler includes.
// These definitions also include the constants specific to the Visual C++ compiler's implementation of Win32
// SEH beyond the facilities provided by the Windows operating systems.  The TEB and PEB are declared near the
// bottom of this file, with all referenced structures recursively defined above them for completeness sake.
//
// Should you be writing low level code, you might find all of these definitions in one spot a handy reference.  If
// you wanted to use this C header file in your own code, you'd probably want to remove the redundant definitions
// (almost all except for the TEB and PEB structures) as they are defined automatically as a result of including
// windows.h.  If you won't be including windows.h or are compiling with GCC under Linux, no changes are
// necessary.
//
// [WINDOWS COMPATIBILITY]
// Both the TEB and PEB structures support Windows NT 3.51 thru Windows 10
//
// [HOW TO ACCESS THESE STRUCTURES]
// The pointers to these structures can be obtained using the following x86 assembly code:
//      mov eax, fs:[18h]   //eax = TEB
//      mov eax, fs:[30h]   //eax = PEB
//
// Or, by using the following Visual C++ compiler intrinsics:
//      void* pTeb = __readfsdword(0x18);
//      void* pPeb = __readfsdword(0x30);
//
// [BUGS]
// This header file is meant mostly for documentation purposes as an alternative to the various tables found
// online; therefore it may contain bugs such that certain members might not be at the offsets stated in the
// comments because I may have forgotten to pad prior members so that everything lines up.  However, I did attempt
// to have all the members line up as documented by each member's offset (see comment to right of each member), so
// please report any bugs or additions to: http://bytepointer.com/contact.htm
//
// [STYLE USED IN THIS FILE] 
// I modified the structures included in this file either from the original official forms found in the Windows
// headers or from various sources online, although the result is functionally equivalent.  The modifications were
// made according to the following scheme for simplicity and clarity:
//
// - array size values are in hex (base-16)
//
// - I avoided creating extraneous pointer types either standalone or as part of the trailing portions of structure
//  definitions.  These take the format Pxxxx where xxxx is the type. Microsoft has historically declared Pxxxx
//  definitions for practically every Windows structure in place of the type identifier with a trailing asterisk.
//  I've always found the trailing asterisk signifying a pointer type to be clearer than the Pxxxx alternative
//  because you can quickly spot them at a glance (especially when syntax hilighting kicks in).
//
// - Windows headers use many aliases for 8, 16, 32 and 64-bit values (UCHAR, ULONG, ULONG_PTR, LONG, LONGLONG, etc.)
//   which are inconsistent at times. I tend to prefer the explicitly specific assembler names: BYTE, WORD, DWORD and
//   QWORD as they are more platform independent names for unsigned values.  Any signed integer type consisting of
//   the term LONG (especially the recursive LONGLONG) just makes me cringe because I don't feel they convey size
//   very well. My naming scheme is therefore:
//
//     BYTE-SIZE                      1     2       4         8
//     unsigned integer types:     BYTE, WORD,  DWORD and QWORD
//     signed integer types:       CHAR, INT16, INT32 and INT64
//
// NOTE: void* and DWORD may be used interchangeably on 32-bit operating systems, however I attempted
//       to use void* (or typed structure pointer where possible) where I was sure the member was to
//       hold a pointer.  Otherwise and where members were to hold padding ints (of any size), I
//       avoided the use of pointer types even when originally declared to be of type PVOID. Also I
//       retained the use of some aliases, such as BOOLEAN, NTSTATUS, HANDLE, etc. only for the
//       purpose of preserving the meaning of the associated structure members.
//
// [MICROSOFT FIRST DOCUMENTS THE TEB and PEB]
// Starting with the release of Visual Studio .NET (2002), Microsoft released a new header, winternl.h
// with the Platform SDK. Within this new header was the first public documentation for the TEB and PEB.
// Microsoft, being legally forced to disclose this information, only released 2 members of the PEB
// (BeingDebugged,SessionId) and 3 members of the TEB (TlsSlots,ReservedForOle,TlsExpansionSlots).
// The original portion of the winternl.h header file is shown below along with Microsoft's usual stern 
// warnings about not using these fields because Windows might change.
//
//      //
//      // The PEB and TEB structures are subject to changes between Windows
//      // releases, thus the fields offsets may change as well as the Reserved
//      // fields.  The Reserved fields are reserved for use only by the Windows
//      // operating systems.  Do not assume a maximum size for the structures.
//      //
//
//      // Instead of using the BeingDebugged field, use the Win32 APIs
//      //     IsDebuggerPresent, CheckRemoteDebuggerPresent
//      // Instead of using the SessionId field, use the Win32 APIs
//      //     GetCurrentProcessId and ProcessIdToSessionId
//      // Sample x86 assembly code that gets the SessionId (subject to change
//      //     between Windows releases, use the Win32 APIs to make your application
//      //     resilient to changes)
//      //     mov     eax,fs:[00000018]
//      //     mov     eax,[eax+0x30]
//      //     mov     eax,[eax+0x1d4]
//      //
//      typedef struct _PEB {
//          BYTE Reserved1[2];
//          BYTE BeingDebugged;
//          BYTE Reserved2[229];
//          PVOID Reserved3[59];
//          ULONG SessionId;
//      } PEB, *PPEB;
//
//      // Instead of using the Tls fields, use the Win32 TLS APIs
//      //     TlsAlloc, TlsGetValue, TlsSetValue, TlsFree
//      //
//      // Instead of using the ReservedForOle field, use the COM API
//      //     CoGetContextToken
//      //
//      typedef struct _TEB {
//          BYTE Reserved1[1952];
//          PVOID Reserved2[412];
//          PVOID TlsSlots[64];
//          BYTE Reserved3[8];
//          PVOID Reserved4[26];
//          PVOID ReservedForOle;  // Windows 2000 only
//          PVOID Reserved5[4];
//          PVOID TlsExpansionSlots;
//      } TEB;
//      typedef TEB *PTEB;
//
// [REFERENCES]
// The information below was compiled from various sources:
//    http://www.geoffchappell.com/studies/windows/win32/ntdll/structs/teb/index.htm
//    http://www.geoffchappell.com/studies/windows/win32/ntdll/structs/peb/index.htm
//    http://terminus.rewolf.pl/terminus/structures/ntdll/_TEB32_x86.html
//    https://en.wikipedia.org/wiki/Win32_Thread_Information_Block
//    http://www.nirsoft.net/kernel_struct/vista/index.html
//    Microsoft's Platform SDK headers / MSDN
//
// [CHANGELIST]
//    2018-10-23:   -bugfix: PEB_LDR_DATA32 struct had "Initialized" member as one BYTE instead of array of 4 BYTE's; also added offsets
//
//    2018-09-17:   -extended PEB for some Win10 members: TppWorkerpListLock, TppWorkerpList, WaitOnAddressHashTable
//
//    2018-04-14:   -offset 0x3 into PEB structure contained a byte bitfield whose last member (SpareBits) erroneously used two bits instead of one;
//                   this caused the bitfield to occupy an extra byte to fit 9 bits; this member has been fixed and now occupies 1 bit.
//                   credit: Chris Eagle
//
//    2018-05-02:   -now can be compiled alongside windows.h (without changes) or by defining WANT_ALL_WINDOWS_H_DEFINITIONS so this file can be used standalone
//                  -this file may also be included alongside tebpeb64.h which can be found at http://bytepointer.com/resources/tebpeb64.h
//                  -increased PEB size to 0x258 for [at least] Windows 10: member addition dwSystemCallMode at offset 0x254
//                   REFERENCE: https://www.malwaretech.com/2015/07/windows-10-system-call-stub-changes.html
//
//    2017-07-29:   initial public release (first stable version)
//

//disable some Visual C++ warnings
#ifdef _MSC_VER
    //when compiling as C
#pragma warning (disable:4214) //Warning Level 4: C4214: nonstandard extension used : bit field types other than int

//"#pragma pack(1)" not needed as Microsoft has designed all structure members to be on natural boundaries

#ifndef STDCALL
#define STDCALL         __stdcall
#endif
#ifndef CDECL
#define CDECL           __cdecl
#endif
#else
    //assume GCC
#ifndef STDCALL
#define STDCALL         __attribute__ ((stdcall))
#endif
#ifndef CDECL
#define CDECL           __attribute__ ((cdecl))
#endif
#endif 

//
// Exception-specific structures and definitions
//

//context flags
#define CONTEXT_i386                    0x00010000                      // this assumes that i386 and
#define CONTEXT_i486                    0x00010000                      // i486 have identical context records
#define CONTEXT_CONTROL                 (CONTEXT_i386 | 0x00000001L)    // SS:SP, CS:IP, FLAGS, BP
#define CONTEXT_INTEGER                 (CONTEXT_i386 | 0x00000002L)    // AX, BX, CX, DX, SI, DI
#define CONTEXT_SEGMENTS                (CONTEXT_i386 | 0x00000004L)    // DS, ES, FS, GS
#define CONTEXT_FLOATING_POINT          (CONTEXT_i386 | 0x00000008L)    // 387 state
#define CONTEXT_DEBUG_REGISTERS         (CONTEXT_i386 | 0x00000010L)    // DB 0-3,6,7
#define CONTEXT_EXTENDED_REGISTERS      (CONTEXT_i386 | 0x00000020L)    // cpu specific extensions
#define CONTEXT_FULL                    (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_SEGMENTS)
#define CONTEXT_ALL                     (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_SEGMENTS | CONTEXT_FLOATING_POINT | CONTEXT_DEBUG_REGISTERS | CONTEXT_EXTENDED_REGISTERS)

//exception flags
#define EXCEPTION_NONCONTINUABLE        0x1     // Noncontinuable exception
#define EXCEPTION_UNWINDING             0x2     // Unwind is in progress; same as EH_UNWINDING
#define EXCEPTION_EXIT_UNWIND           0x4     // Exit unwind is in progress; same as EH_EXIT_UNWIND
#define EXCEPTION_STACK_INVALID         0x8     // Stack out of limits or unaligned
#define EXCEPTION_NESTED_CALL           0x10    // Nested exception handler call
#define EXCEPTION_TARGET_UNWIND         0x20    // Target unwind in progress
#define EXCEPTION_COLLIDED_UNWIND       0x40    // Collided exception handler call
#define EXCEPTION_UNWIND                (EXCEPTION_UNWINDING | EXCEPTION_EXIT_UNWIND | EXCEPTION_TARGET_UNWIND | EXCEPTION_COLLIDED_UNWIND)
#define IS_UNWINDING(Flag)              ((Flag & EXCEPTION_UNWIND) != 0)
#define IS_DISPATCHING(Flag)            ((Flag & EXCEPTION_UNWIND) == 0)
#define IS_TARGET_UNWIND(Flag)          (Flag & EXCEPTION_TARGET_UNWIND)

//msvc exception filter expression return codes
#define EXCEPTION_EXECUTE_HANDLER       1   //same as FILTER_ACCEPT
#define EXCEPTION_CONTINUE_SEARCH       0   //same as FILTER_CONTINUE_SEARCH
#define EXCEPTION_CONTINUE_EXECUTION    -1  //same as FILTER_DISMISS

#ifdef WANT_ALL_WINDOWS_H_DEFINITIONS

//exception handler (disposition) return values
typedef enum _EXCEPTION_DISPOSITION
{
    ExceptionContinueExecution,         //0; same as DISPOSITION_DISMISS, _XCPT_CONTINUE_EXECUTION
    ExceptionContinueSearch,            //1; same as DISPOSITION_CONTINUE_SEARCH, _XCPT_CONTINUE_SEARCH
    ExceptionNestedException,           //2; same as DISPOSITION_NESTED_EXCEPTION
    ExceptionCollidedUnwind             //3; same as DISPOSITION_COLLIDED_UNWIND
} EXCEPTION_DISPOSITION;

#define EXCEPTION_MAXIMUM_PARAMETERS 15
typedef struct EXCEPTION_RECORD EXCEPTION_RECORD;
struct EXCEPTION_RECORD //size=0x50
{
    DWORD               ExceptionCode;                                          //0x00
    DWORD               ExceptionFlags;                                         //0x04 - see possible values above
    EXCEPTION_RECORD* ExceptionRecord;                                        //0x08
    void* ExceptionAddress;                                       //0x0C
    DWORD               NumberParameters;                                       //0x10
    DWORD               ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];     //0x14
};

#define SIZE_OF_80387_REGISTERS 80
typedef struct _FLOATING_SAVE_AREA //size=0x70
{
    DWORD   ControlWord;                                //0x00
    DWORD   StatusWord;                                 //0x04
    DWORD   TagWord;                                    //0x08
    DWORD   ErrorOffset;                                //0x0C
    DWORD   ErrorSelector;                              //0x10
    DWORD   DataOffset;                                 //0x14
    DWORD   DataSelector;                               //0x18
    BYTE    RegisterArea[SIZE_OF_80387_REGISTERS];      //0x1C
    DWORD   Cr0NpxState;                                //0x6C
} FLOATING_SAVE_AREA;

#define MAXIMUM_SUPPORTED_EXTENSION 512
typedef struct _CONTEXT //size=0x2CC
{
    //determines which groups of members are valid
    DWORD               ContextFlags;                                       //0x00 - see possible values above
    //following member group valid when CONTEXT_DEBUG_REGISTERS set
    DWORD               Dr0;                                                //0x04
    DWORD               Dr1;                                                //0x08
    DWORD               Dr2;                                                //0x0C
    DWORD               Dr3;                                                //0x10
    DWORD               Dr6;                                                //0x14
    DWORD               Dr7;                                                //0x18
    //following member valid when CONTEXT_FLOATING_POINT set
    FLOATING_SAVE_AREA  FloatSave;                                          //0x1C
    //following member group valid when CONTEXT_SEGMENTS set 
    DWORD               SegGs;                                              //0x8C
    DWORD               SegFs;                                              //0x90
    DWORD               SegEs;                                              //0x94
    DWORD               SegDs;                                              //0x98
    //following member group valid when CONTEXT_INTEGER set
    DWORD               Edi;                                                //0x9C
    DWORD               Esi;                                                //0xA0
    DWORD               Ebx;                                                //0xA4
    DWORD               Edx;                                                //0xA8
    DWORD               Ecx;                                                //0xAC
    DWORD               Eax;                                                //0xB0
    //following member group valid when CONTEXT_CONTROL set
    DWORD               Ebp;                                                //0xB4
    DWORD               Eip;                                                //0xB8
    DWORD               SegCs;                                              //0xBC
    DWORD               EFlags;                                             //0xC0
    DWORD               Esp;                                                //0xC4
    DWORD               SegSs;                                              //0xC8
    //following member valid when CONTEXT_EXTENDED_REGISTERS set
    BYTE                ExtendedRegisters[MAXIMUM_SUPPORTED_EXTENSION];     //0xCC
} CONTEXT;

//used with UnhandledExceptionFilter()/SetUnhandledExceptionFilter() and newer Vectored Exception handling functions
typedef struct _EXCEPTION_POINTERS
{
    EXCEPTION_RECORD* ExceptionRecord;
    CONTEXT* ContextRecord;
} EXCEPTION_POINTERS;

#endif //WANT_ALL_WINDOWS_H_DEFINITIONS

typedef struct EXCEPTION_REGISTRATION EXCEPTION_REGISTRATION;

//exception handler signatures
typedef EXCEPTION_DISPOSITION(CDECL* ExceptionHandler)(EXCEPTION_RECORD* ExceptionRecord, EXCEPTION_REGISTRATION* EstablisherFrame, CONTEXT* ContextRecord, void* DispatcherContext); //same as EXCEPTION_ROUTINE and _except_handler
typedef INT32(STDCALL* TopLevelExceptionFilter)(EXCEPTION_POINTERS* ExceptionInfo); //same as TOP_LEVEL_EXCEPTION_FILTER for SetUnhandledExceptionFilter();  
typedef INT32(STDCALL* VectoredExceptionHandler)(EXCEPTION_POINTERS* ExceptionInfo); //same as PVECTORED_EXCEPTION_HANDLER and above signature used with AddVectoredExceptionHandler(), RemoveVectoredExceptionHandler() for XP/WS03 and up

//stack exception frame a.k.a. EXCEPTION_REGISTRATION_RECORD
struct EXCEPTION_REGISTRATION
{
    EXCEPTION_REGISTRATION* prev;
    ExceptionHandler* handler;
};
#define EXCEPTION_CHAIN_END ((EXCEPTION_REGISTRATION*)-1)


//
// PEB-specific structures
//

//forward declarations for unknown structures
typedef struct _ACTIVATION_CONTEXT_DATA { void* dummy; } ACTIVATION_CONTEXT_DATA; //XP and up
typedef struct _ASSEMBLY_STORAGE_MAP { void* dummy; } ASSEMBLY_STORAGE_MAP;       //XP and up
typedef struct _FLS_CALLBACK_INFO { void* dummy; } FLS_CALLBACK_INFO;             //WS03 and up

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
    WORD       Flags;
    WORD       Length;
    DWORD      TimeStamp;
    STRING     DosPath;
} RTL_DRIVE_LETTER_CURDIR;

typedef struct _PEB_LDR_DATA32
{
    DWORD          Length;                             //0x00
    BYTE           Initialized[4];                     //0x04
    void* SsHandle;                           //0x08
    LIST_ENTRY     InLoadOrderModuleList;              //0x0C
    LIST_ENTRY     InMemoryOrderModuleList;            //0x14
    LIST_ENTRY     InInitializationOrderModuleList;    //0x1C
    void* EntryInProgress;                    //0x24
} PEB_LDR_DATA32;

typedef struct PEB_FREE_BLOCK PEB_FREE_BLOCK;
struct PEB_FREE_BLOCK
{
    PEB_FREE_BLOCK* Next;
    DWORD              Size;
};

typedef struct _RTL_USER_PROCESS_PARAMETERS32
{
    DWORD                   MaximumLength;                 //0x00 
    DWORD                   Length;                        //0x04 
    DWORD                   Flags;                         //0x08 
    DWORD                   DebugFlags;                    //0x0C 
    void* ConsoleHandle;                 //0x10 
    DWORD                   ConsoleFlags;                  //0x14 
    HANDLE                  StdInputHandle;                //0x18 
    HANDLE                  StdOutputHandle;               //0x1C 
    HANDLE                  StdErrorHandle;                //0x20 
    UNICODE_STRING          CurrentDirectoryPath;          //0x24 
    HANDLE                  CurrentDirectoryHandle;        //0x2C 
    UNICODE_STRING          DllPath;                       //0x30 
    UNICODE_STRING          ImagePathName;                 //0x38 
    UNICODE_STRING          CommandLine;                   //0x40 
    void* Environment;                   //0x48 
    DWORD                   StartingPositionLeft;          //0x4C 
    DWORD                   StartingPositionTop;           //0x50 
    DWORD                   Width;                         //0x54 
    DWORD                   Height;                        //0x58 
    DWORD                   CharWidth;                     //0x5C 
    DWORD                   CharHeight;                    //0x60 
    DWORD                   ConsoleTextAttributes;         //0x64 
    DWORD                   WindowFlags;                   //0x68 
    DWORD                   ShowWindowFlags;               //0x6C 
    UNICODE_STRING          WindowTitle;                   //0x70 
    UNICODE_STRING          DesktopName;                   //0x78 
    UNICODE_STRING          ShellInfo;                     //0x80 
    UNICODE_STRING          RuntimeData;                   //0x88 
    RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];      //0x90 
} RTL_USER_PROCESS_PARAMETERS32;

//
// PEB (Process Environment Block) 32-bit
//
// The size of this structure is OS dependent:
//    0x0098    NT 3.51
//    0x0150    NT 4.0
//    0x01E8    Win2k
//    0x020C    XP
//    0x0230    WS03
//    0x0238    Vista
//    0x0240    Win7_BETA
//    0x0248    Win6
//    0x0250    Win8
//    0x045C    Win10
//
typedef struct _PEB32
{
    BOOLEAN                         InheritedAddressSpace;              //0x0000
    BOOLEAN                         ReadImageFileExecOptions;           //0x0001
    BOOLEAN                         BeingDebugged;                      //0x0002
    union
    {
        BOOLEAN                     SpareBool;                          //0x0003 (NT3.51-late WS03)
        struct
        {
            BYTE                    ImageUsesLargePages : 1;   //0x0003:0 (WS03_SP1+)
            BYTE                    IsProtectedProcess : 1;   //0x0003:1 (Vista+)
            BYTE                    IsLegacyProcess : 1;   //0x0003:2 (Vista+)
            BYTE                    IsImageDynamicallyRelocated : 1;   //0x0003:3 (Vista+)
            BYTE                    SkipPatchingUser32Forwarders : 1;   //0x0003:4 (Vista_SP1+)
            BYTE                    IsPackagedProcess : 1;   //0x0003:5 (Win8_BETA+)
            BYTE                    IsAppContainer : 1;   //0x0003:6 (Win8_RTM+)
            BYTE                    SpareBit : 1;   //0x0003:7
        } bits;
    } byte3;
    uint32_t                          Mutant;                             //0x0004
    uint32_t ImageBaseAddress;                   //0x0008
    uint32_t Ldr;                                //0x000C  (all loaded modules in process)
    uint32_t ProcessParameters;                  //0x0010
    uint32_t SubSystemData;                      //0x0014
    uint32_t ProcessHeap;                        //0x0018
    uint32_t FastPebLock;                        //0x001C
    union
    {
        uint32_t FastPebLockRoutine;                 //0x0020 (NT3.51-Win2k)
        uint32_t SparePtr1;                          //0x0020 (early WS03)
        uint32_t AtlThunkSListPtr;                   //0x0020 (late WS03+)
    } dword20;
    union
    {
        uint32_t FastPebUnlockRoutine;               //0x0024 (NT3.51-XP)
        uint32_t SparePtr2;                          //0x0024 (WS03)
        uint32_t IFEOKey;                            //0x0024 (Vista+)
    } dword24;
    union
    {
        DWORD                       EnvironmentUpdateCount;             //0x0028 (NT3.51-WS03)
        struct
        {
            DWORD                   ProcessInJob : 1;        //0x0028:0 (Vista+)
            DWORD                   ProcessInitializing : 1;        //0x0028:1 (Vista+)
            DWORD                   ProcessUsingVEH : 1;        //0x0028:2 (Vista_SP1+)
            DWORD                   ProcessUsingVCH : 1;        //0x0028:3 (Vista_SP1+)
            DWORD                   ProcessUsingFTH : 1;        //0x0028:4 (Win7_BETA+)
            DWORD                   ReservedBits0 : 27;       //0x0028:5 (Win7_BETA+)
        } vista_CrossProcessFlags;
    } struct28;
    union
    {
        uint32_t KernelCallbackTable;                //0x002C (Vista+)
        uint32_t UserSharedInfoPtr;                  //0x002C (Vista+)
    } dword2C;
    DWORD                           SystemReserved;                     //0x0030 (NT3.51-XP)
    //Microsoft seems to keep changing their mind with DWORD 0x34
    union
    {
        DWORD                       SystemReserved2;                    //0x0034 (NT3.51-Win2k)
        struct
        {
            DWORD                   ExecuteOptions : 2;        //0x0034:0 (XP-early WS03) 
            DWORD                   SpareBits : 30;       //0x0034:2 (XP-early WS03)
        } xpBits;
        DWORD                       AtlThunkSListPtr32;                 //0x0034 (late XP,Win7+)
        DWORD                       SpareUlong;                         //0x0034 (late WS03-Vista)
        struct
        {
            DWORD                   HeapTracingEnabled : 1;        //0x0034:0 (Win7_BETA)
            DWORD                   CritSecTracingEnabled : 1;        //0x0034:1 (Win7_BETA)
            DWORD                   SpareTracingBits : 30;       //0x0034:2 (Win7_BETA)
        } win7_TracingFlags;
    } dword34;
    union
    {
        uint32_t FreeList;                           //0x0038 (NT3.51-early Vista)
        DWORD                       SparePebPtr0;                       //0x0038 (last Vista)
        uint32_t ApiSetMap;                          //0x0038 (Win7+)
    } dword38;
    DWORD                           TlsExpansionCounter;                //0x003C
    uint32_t TlsBitmap;                          //0x0040
    DWORD                           TlsBitmapBits[2];                   //0x0044
    uint32_t ReadOnlySharedMemoryBase;           //0x004C
    union
    {
        uint32_t ReadOnlyShareMemoryHeap;            //0x0050 (NT3.51-WS03)
        uint32_t HotpatchInformation;                //0x0050 (Vista+)
    } dword50;
    uint32_t ReadOnlyStaticServerData;           //0x0054
    uint32_t AnsiCodePageData;                   //0x0058
    uint32_t OemCodePageData;                    //0x005C
    uint32_t UnicodeCaseTableData;               //0x0060
    DWORD                           NumberOfProcessors;                 //0x0064
    DWORD                           NtGlobalFlag;                       //0x0068
    LARGE_INTEGER                   CriticalSectionTimeout;             //0x0070
    DWORD                           HeapSegmentReserve;                 //0x0078
    DWORD                           HeapSegmentCommit;                  //0x007C
    DWORD                           HeapDeCommitTotalFreeThreshold;     //0x0080
    DWORD                           HeapDeCommitFreeBlockThreshold;     //0x0084
    DWORD                           NumberOfHeaps;                      //0x0088
    DWORD                           MaximumNumberOfHeaps;               //0x008C
    uint32_t ProcessHeaps;                       //0x0090
    uint32_t GdiSharedHandleTable;               //0x0094

    //end of NT 3.51 members / members that follow available on NT 4.0 and up

    uint32_t ProcessStarterHelper;               //0x0098
    DWORD                           GdiDCAttributeList;                 //0x009C
    union
    {
        struct
        {
            uint32_t LoaderLock;                         //0x00A0 (NT4)
        } nt4;
        struct
        {
            uint32_t LoaderLock;                         //0x00A0 (Win2k+)
        } win2k;
    } dwordA0;
    DWORD                           OSMajorVersion;                     //0x00A4
    DWORD                           OSMinorVersion;                     //0x00A8
    WORD                            OSBuildNumber;                      //0x00AC
    WORD                            OSCSDVersion;                       //0x00AE
    DWORD                           OSPlatformId;                       //0x00B0
    DWORD                           ImageSubsystem;                     //0x00B4
    DWORD                           ImageSubsystemMajorVersion;         //0x00B8
    DWORD                           ImageSubsystemMinorVersion;         //0x00BC
    union
    {
        KAFFINITY                   ImageProcessAffinityMask;           //0x00C0 (NT4-early Vista)
        KAFFINITY                   ActiveProcessAffinityMask;          //0x00C0 (late Vista+)
    } dwordC0;
    DWORD                           GdiHandleBuffer[0x22];              //0x00C4
    uint32_t PostProcessInitRoutine;             //0x014C / void (*PostProcessInitRoutine) (void);

    //members that follow available on Windows 2000 and up

    uint32_t TlsExpansionBitmap;                 //0x0150
    DWORD                           TlsExpansionBitmapBits[0x20];       //0x0154
    DWORD                           SessionId;                          //0x01D4
    ULARGE_INTEGER                  AppCompatFlags;                     //0x01D8
    ULARGE_INTEGER                  AppCompatFlagsUser;                 //0x01E0
    uint32_t pShimData;                          //0x01E8
    uint32_t AppCompatInfo;                      //0x01EC
    UNICODE_STRING                  CSDVersion;                         //0x01F0

    //members that follow available on Windows XP and up

    ACTIVATION_CONTEXT_DATA* ActivationContextData;              //0x01F8
    ASSEMBLY_STORAGE_MAP* ProcessAssemblyStorageMap;          //0x01FC
    ACTIVATION_CONTEXT_DATA* SystemDefaultActivationContextData; //0x0200
    ASSEMBLY_STORAGE_MAP* SystemAssemblyStorageMap;           //0x0204
    DWORD                           MinimumStackCommit;                 //0x0208

    //members that follow available on Windows Server 2003 and up

    FLS_CALLBACK_INFO* FlsCallback;                        //0x020C
    LIST_ENTRY                      FlsListHead;                        //0x0210
    uint32_t FlsBitmap;                          //0x0218
    DWORD                           FlsBitmapBits[4];                   //0x021C
    DWORD                           FlsHighIndex;                       //0x022C

    //members that follow available on Windows Vista and up

    uint32_t WerRegistrationData;                //0x0230
    uint32_t WerShipAssertPtr;                   //0x0234

    //members that follow available on Windows 7 BETA and up

    union
    {
        uint32_t pContextData;                       //0x0238 (prior to Windows 8)
        uint32_t pUnused;                            //0x0238 (Windows 8)
    } dword238;
    uint32_t pImageHeaderHash;                   //0x023C

    //members that follow available on Windows 7 RTM and up

    struct //TracingFlags
    {
        DWORD                       HeapTracingEnabled : 1;        //0x0240:0
        DWORD                       CritSecTracingEnabled : 1;        //0x0240:1
        DWORD                       LibLoaderTracingEnabled : 1;        //0x0240:2
        DWORD                       SpareTracingBits : 29;       //0x0240:3
    } dword240;
    DWORD                           dummy02;                            //0x0244

    //members that follow available on Windows 8 and up
    QWORD                           CsrServerReadOnlySharedMemoryBase;  //0x0248

    //members that follow available on Windows 10 and up
    DWORD                           TppWorkerpListLock;                 //0x0250
    union //conflicting reports about what 0x254 points to
    {
        LIST_ENTRY                  TppWorkerpList;                     //0x0254
        DWORD                       dwSystemCallMode;                   //0x0254 / set to 2 under 64-bit Windows in a 32-bit process (WOW64)
    } dword254;
    uint32_t WaitOnAddressHashTable[128];        //0x025C

} PEB32;


//
// TEB-specific structures
//

//GDI_TEB_BATCH - size=0x04E0
typedef struct _GDI_TEB_BATCH
{
    union
    {
        DWORD   Offset;
        struct
        {
            DWORD Offset : 31;  //0x00:00  Win 8.1 Update 1+
            DWORD HasRenderingCommand : 1;   //0x00:31  Win 8.1 Update 1+
        } bits;
    } dword0;
    DWORD   HDC;
    DWORD   Buffer[0x136];
} GDI_TEB_BATCH;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT
{
    DWORD  Flags;
    CHAR* FrameName;
} TEB_ACTIVE_FRAME_CONTEXT;

typedef struct TEB_ACTIVE_FRAME TEB_ACTIVE_FRAME;
struct TEB_ACTIVE_FRAME
{
    DWORD                      Flags;
    TEB_ACTIVE_FRAME* Previous;
    TEB_ACTIVE_FRAME_CONTEXT* Context;
};

//
// TEB (Thread Environment Block) a.k.a. TIB (Thread Information Block) 32-bit
//
// The size of this structure is OS dependent:
//    0x0F28    NT 3.51
//    0x0F88    NT 4.0
//    0x0FA4    Win2k
//    0x0FB4    prior to XP SP2
//    0x0FB8    XP SP2/WS03+
//    0x0FBC    WS03 SP1+
//    0x0FF8    Vista/WS08
//    0x0FE4    Win7/WS08 R2
//    0x0FE8    Win8-Win8.1/WS12
//    0x1000    Win10
//
typedef struct TEB32 TEB32;
struct TEB32
{
    //NT_TIB structure portion
    EXCEPTION_REGISTRATION* ExceptionList;                              //0x0000 / Current Structured Exception Handling (SEH) frame
    uint32_t StackBase;                                  //0x0004 / Bottom of stack (high address)
    uint32_t StackLimit;                                 //0x0008 / Ceiling of stack (low address)
    uint32_t SubSystemTib;                               //0x000C
    union
    {
        void* FiberData;                                  //0x0010
        DWORD                   Version;                                    //0x0010
    } dword10;
    void* ArbitraryUserPointer;                       //0x0014
    TEB* Self;                                       //0x0018
    //NT_TIB ends (NT subsystem independent part)

    void* EnvironmentPointer;                         //0x001C
    CLIENT_ID                   ClientId;                                   //0x0020
    //                          ClientId.ProcessId                          //0x0020 / value retrieved by GetCurrentProcessId()
    //                          ClientId.ThreadId                           //0x0024 / value retrieved by GetCurrentThreadId()
    void* ActiveRpcHandle;                            //0x0028
    void* ThreadLocalStoragePointer;                  //0x002C
    PEB32* ProcessEnvironmentBlock;                    //0x0030
    DWORD                       LastErrorValue;                             //0x0034
    DWORD                       CountOfOwnedCriticalSections;               //0x0038
    void* CsrClientThread;                            //0x003C
    void* Win32ThreadInfo;                            //0x0040
    DWORD                       User32Reserved[0x1A];                       //0x0044
    DWORD                       UserReserved[5];                            //0x00AC
    void* WOW32Reserved;                              //0x00C0 / user-mode 32-bit (WOW64) -> 64-bit context switch function prior to kernel-mode transition
    LCID                        CurrentLocale;                              //0x00C4
    DWORD                       FpSoftwareStatusRegister;                   //0x00C8
    union
    {
        DWORD                   SystemReserved1[0x36];                      //0x00CC (NT 3.51-Win8)
        struct
        {
            DWORD               Reserved1[0x16];                            //0x00CC
            void* pKThread;                                   //0x0124 / pointer to KTHREAD (ETHREAD) structure
            DWORD               Reserved2[0x1F];                            //0x0128
        } kernelInfo;
        struct
        {
            DWORD               ReservedForDebuggerInstrumentation[0x10];   //0x00CC (Win10 PRE-RTM+)
            DWORD               SystemReserved1[0x26];                      //0x010C (Win10 PRE-RTM+)
        } win10;
    } dwordCC;
    NTSTATUS                    ExceptionCode;                              //0x01A4
    union
    {
        BYTE                    SpareBytes1[0x2C];                          //0x01A8 (NT3.51-Win2k)
        struct
        {
            BYTE                ActivationContextStack[0x14];               //0x01A8 (XP-early WS03)
            BYTE                SpareBytes1[0x18];                          //0x01BC (XP-early WS03)
        } xp;
        struct
        {
            void* ActivationContextStackPointer;              //0x01A8 (WS03+)
            union
            {
                BYTE            SpareBytes1[0x24];                          //0x01AC (WS03-Win8.1)
                struct
                {
                    void* InstrumentationCallbackSp;                  //0x01AC (Win10+)
                    void* InstrumentationCallbackPreviousPc;          //0x01B0 (Win10+)
                    void* InstrumentationCallbackPreviousSp;          //0x01B4 (Win10+)
                    BOOLEAN     InstrumentationCallbackDisabled;            //0x01B8 (Win10+)
                    BYTE        SpareBytes[0x17];                           //0x01B9 (Win10+)
                } win10;
            } dword1AC;
            union
            {
                BYTE            SpareBytes2[4];                             //0x01D0 (WS03)
                DWORD           TxFsContext;                                //0x01D0 (Vista+)
            } dword1D0;
        } lateWs03;
    } dword1A8;
    GDI_TEB_BATCH               GdiTebBatch;                                //0x01D4
    CLIENT_ID                   RealClientId;                               //0x06B4
    HANDLE                      GdiCachedProcessHandle;                     //0x06BC
    DWORD                       GdiClientPID;                               //0x06C0
    DWORD                       GdiClientTID;                               //0x06C4
    void* GdiThreadLocalInfo;                         //0x06C8
    DWORD                       Win32ClientInfo[0x3E];                      //0x06CC
    void* glDispatchTable[0xE9];                      //0x07C4
    DWORD                       glReserved1[0x1D];                          //0x0B68
    void* glReserved2;                                //0x0BDC
    void* glSectionInfo;                              //0x0BE0
    void* glSection;                                  //0x0BE4
    void* glTable;                                    //0x0BE8
    void* glCurrentRC;                                //0x0BEC
    void* glContext;                                  //0x0BF0
    NTSTATUS                    LastStatusValue;                            //0x0BF4
    UNICODE_STRING              StaticUnicodeString;                        //0x0BF8
    WCHAR                       StaticUnicodeBuffer[0x105];                 //0x0C00
    void* DeallocationStack;                          //0x0E0C
    void* TlsSlots[0x40];                             //0x0E10
    LIST_ENTRY                  TlsLinks;                                   //0x0F10
    void* Vdm;                                        //0x0F18
    void* ReservedForNtRpc;                           //0x0F1C
    void* DbgSsReserved[2];                           //0x0F20

    //end of NT 3.51 members / members that follow available on NT 4.0 and up

    union
    {
        DWORD                   ThreadErrorMode;                            //0x0F28 (OS?) / RtlSetThreadErrorMode
        DWORD                   HardErrorsAreDisabled;                      //0x0F28 (NT4-XP)
        DWORD                   HardErrorMode;                              //0x0F28 (WS03+)
    } dwordF28;
    union
    {
        struct
        {
            DWORD               Instrumentation[0x10];                      //0x0F2C (NT4-early WS03)
        } nt;
        struct
        {
            union
            {
                struct
                {
                    DWORD       Instrumentation[0x0E];                      //0x0F2C (late WS03+)
                    void* SubProcessTag;                              //0x0F64 (late WS03+)
                } beforeVista;
                struct
                {
                    DWORD       Instrumentation[9];                         //0x0F2C (Vista+)
                    GUID        ActivityId;                                 //0x0F50 (Vista+)
                    void* SubProcessTag;                              //0x0F60 (Vista+)
                    union
                    {
                        DWORD   EtwLocalData;                               //0x0F64 (WIN8 PRE-RTM)
                        DWORD   PerflibData;                                //0x0F64 (WIN8 RTM+)
                    } win8;

                } vista;
            } dwordF2C;
            void* EtwTraceData;                               //0x0F68 (late WS03+)
        } ws03;
    } dwordF2C;
    void* WinSockData;                                //0x0F6C
    DWORD                       GdiBatchCount;                              //0x0F70
    union
    {
        struct
        {
            union
            {
                struct
                {
                    BOOLEAN     InDbgPrint;                                 //0x0F74 (NT4-WS03)
                    BOOLEAN     FreeStackOnTermination;                     //0x0F75 (NT4-WS03)
                    BOOLEAN     HasFiberData;                               //0x0F76 (NT4-WS03)
                } beforeVista;
                union
                {
                    BOOLEAN     SpareBool0;                                 //0x0F74 (Vista)
                    BOOLEAN     SpareBool1;                                 //0x0F75 (Vista)
                    BOOLEAN     SpareBool2;                                 //0x0F76 (Vista)
                } vista;
            } u;
            BOOLEAN             IdealProcessor;                             //0x0F77 (NT4-Vista)
        } beforeWin7;
        PROCESSOR_NUMBER        CurrentIdealProcessor;                      //0x0F74 (Win7+)
    } dwordF74;
    union
    {
        DWORD                   Spare3;                                     //0x0F78 (NT4-early WS03)
        DWORD                   GuaranteedStackBytes;                       //0x0F78 (late WS03+)
    } dwordF78;
    void* ReservedForPerf;                            //0x0F7C
    void* ReservedForOle;                             //0x0F80
    DWORD                       WaitingOnLoaderLock;                        //0x0F84

    //members that follow available on Windows 2000 and up

    union
    {
        struct
        {
            //Wx86ThreadState structure
            DWORD* CallBx86Eip;                                //0x0F88 (Win2k-early WS03)
            void* DeallocationCpu;                            //0x0F8C (Win2k-early WS03)
            BYTE                UseKnownWx86Dll;                            //0x0F90 (Win2k-early WS03)
            CHAR                OleStubInvoked;                             //0x0F91 (Win2k-early WS03)
            BYTE                Padding[2];                                 //0x0F92
        } beforeLateWs03;
        struct
        {
            union
            {
                void* SparePointer1;                              //0x0F88 (late WS03)
                void* SavedPriorityState;                         //0x0F88 (Vista+)
            } dwordF88;
            union
            {
                void* SoftPatchPtr1;                              //0x0F8C (late WS03-Win7)
                void* ReservedForCodeCoverage;                    //0x0F8C (Win8+)
            } dwordF8C;
            union
            {
                void* SoftPatchPtr2;                              //0x0F90 (late WS03)
                void* ThreadPoolData;                             //0x0F90 (Vista+)
            } dwordF90;
        } lateWs03;
    } dwordF88;
    void* TlsExpansionSlots;                          //0x0F94
    union
    {
        LCID                    ImpersonationLocale;                        //0x0F98 (Win2k-Vista)
        DWORD                   MuiGeneration;                              //0x0F98 (Win7+)
    } dwordF98;
    DWORD                       IsImpersonating;                            //0x0F9C
    void* NlsCache;                                   //0x0FA0

    //members that follow available on Windows XP and up

    void* pShimData;                                  //0x0FA4
    union
    {
        DWORD                   HeapVirtualAffinity;                        //0x0FA8 (XP-Win7)
        struct
        {
            WORD                HeapVirtualAffinity;                        //0x0FA8 (Win8+)
            WORD                LowFragHeapDataSlot;                        //0x0FAA (Win8+)
        } win8;
    } dwordFA8;
    HANDLE                      CurrentTransactionHandle;                   //0x0FAC
    TEB_ACTIVE_FRAME* ActiveFrame;                                //0x0FB0

    //members that follow available on Windows XP SP2 and up

    union
    {
        void* FlsData;                                    //0x0FB4 (WS03+)
        struct
        {
            BOOLEAN             SafeThunkCall;                              //0x0FB4 (XP SP2)
            BOOLEAN             BooleanSpare[3];                            //0x0FB5 (XP SP2)
        } xpSp2;
    } dwordFB4;
    union
    {
        struct
        {
            BOOLEAN             SafeThunkCall;                              //0x0FB8 (late WS03)
            BOOLEAN             BooleanSpare[3];                            //0x0FB9 (late WS03)
        } ws03;
        void* PreferredLanguages;                         //0x0FB8 (Vista+)
    } dwordFB8;

    //members that follow available on Windows Vista and up

    void* UserPrefLanguages;                          //0x0FBC
    void* MergedPrefLanguages;                        //0x0FC0
    DWORD                       MuiImpersonation;                           //0x0FC4
    union
    {
        volatile WORD           CrossTebFlags;                              //0x0FC8
        struct
        {
            WORD                SpareCrossTebBits : 16;                     //0x0FC8
        } bits;
    } wordFC8;
    union
    {
        WORD                    SameTebFlags;                               //0x0FCA
        struct
        {
            WORD                SafeThunkCall : 1;                   //0x0FCA:0x00
            WORD                InDebugPrint : 1;                   //0x0FCA:0x01
            WORD                HasFiberData : 1;                   //0x0FCA:0x02
            WORD                SkipThreadAttach : 1;                   //0x0FCA:0x03
            WORD                WerInShipAssertCode : 1;                   //0x0FCA:0x04
            WORD                RanProcessInit : 1;                   //0x0FCA:0x05
            WORD                ClonedThread : 1;                   //0x0FCA:0x06
            WORD                SuppressDebugMsg : 1;                   //0x0FCA:0x07
            WORD                DisableUserStackWalk : 1;                   //0x0FCA:0x08
            WORD                RtlExceptionAttached : 1;                   //0x0FCA:0x09
            WORD                InitialThread : 1;                   //0x0FCA:0x0A
            WORD                SessionAware : 1;                   //0x0FCA:0x0B            
        } bits;
    } wordFCA;
    void* TxnScopeEnterCallback;                      //0x0FCC
    void* TxnScopeExitCallback;                       //0x0FD0
    void* TxnScopeContext;                            //0x0FD4
    DWORD                       LockCount;                                  //0x0FD8
    union
    {
        struct
        {
            DWORD               ProcessRundown;                             //0x0FDC (Vista)
            QWORD               LastSwitchTime;                             //0x0FE0 (Vista)
            QWORD               TotalSwitchOutTime;                         //0x0FE8 (Vista)
            LARGE_INTEGER       WaitReasonBitMap;                           //0x0FF0 (Vista)
        } vista;

        //end of Vista members

        struct
        {
            union
            {
                DWORD           SpareUlong0;                                //0x0FDC (Win7-Win8)
                INT32           WowTebOffset;                               //0x0FDC (Win10+)
            } dwordFDC;
            void* ResourceRetValue;                           //0x0FE0 (Win7+)

            //end of Windows 7 members (TEB shrunk after Vista)

            void* ReservedForWdf;                             //0x0FE4 (Win8+)

            //end of Windows 8 members

        } afterVista;
    } dwordFDC;

    //members that follow available on Windows 10 and up (currently unknown)

    BYTE                        ReservedForWin10[0x18];                     //0x0FE8

}; //struct TEB
