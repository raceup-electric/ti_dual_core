#ifndef SD_CARD_H_
#define SD_CARD_H_

#include "F28x_Project.h"
//#include "driverlib.h"
//#include "device.h"
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "utils/cmdline.h"
#include "utils/ustdlib.h"
//#include "third_party/fatfs/src/ff.h"
//#include "third_party/fatfs/src/diskio.h"
#include "ff.h"
#include "diskio.h"

//
// Defines
//
#define PATH_BUF_SIZE   80     // Defines the size of the buffers that hold the
                               // path, or temporary data from the SD card.
                               // There are two buffers allocated of this size.
                               // The buffer size must be large enough to hold
                               // the longest expected full path name,
                               // including the file name, and a trailing null
                               // character.
#define CMD_BUF_SIZE    300     // Defines the size of the buffer that holds
                               // the command line.
#define FRESULT_ENTRY(f)        { (f), (# f) } // A macro to make it easy to
                                               // add result codes to the table
#define NAME_TOO_LONG_ERROR     1              // Error reasons returned
#define OPENDIR_ERROR           2              // by ChangeDirectory().
#define NUM_FRESULT_CODES (sizeof(g_sFresultStrings) / sizeof(tFresultString))
#define TICKS_PER_SECOND        100
#define NUM_LIST_STRINGS        48
#define MAX_FILENAME_STRING_LEN (4 + 8 + 1 + 3 + 1)
#define NUM_STATUS_STRINGS      6
#define MAX_STATUS_STRING_LEN   (36 + 1)

//
// Globals
//
static char g_cCwdBuf[PATH_BUF_SIZE] = "/";  // This buffer holds the full path
                                             // to the current working
                                             // directory. Initially it is
                                             // root ("/").
static char g_cTmpBuf[PATH_BUF_SIZE];        // A temporary data buffer used
                                             // when manipulating file paths,or
                                             // reading data from the SD card.
static char g_cCmdBuf[CMD_BUF_SIZE];         // The buffer that holds the
                                             // command line.
static FATFS g_sFatFs;
static DIR g_sDirObject;
static FILINFO g_sFileInfo;
static FIL g_sFileObject;


static FRESULT ChangeToDirectory(char *pcDirectory, unsigned long *pulReason);
static const char *StringFromFresult(FRESULT fresult);

void setupSD(void);
void writeSD(char *str);



#endif
