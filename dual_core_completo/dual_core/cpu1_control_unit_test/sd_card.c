
#include "sd_card.h"

int var = 5;
BYTE diskResult;

//
// A structure that holds a mapping between an FRESULT numerical code,
// and a string representation.  FRESULT codes are returned from the FatFs
// FAT file system driver.
//
typedef struct
{
    FRESULT fresult;
    char *pcResultStr;
}
tFresultString;

//
// A table that holds a mapping between the numerical FRESULT code and
// it's name as a string.  This is used for looking up error codes for
// printing to the console.
//
tFresultString g_sFresultStrings[] =
{
    FRESULT_ENTRY(FR_OK),
    FRESULT_ENTRY(FR_NOT_READY),
    FRESULT_ENTRY(FR_NO_FILE),
    FRESULT_ENTRY(FR_NO_PATH),
    FRESULT_ENTRY(FR_INVALID_NAME),
    FRESULT_ENTRY(FR_INVALID_DRIVE),
    FRESULT_ENTRY(FR_DENIED),
    FRESULT_ENTRY(FR_EXIST),
    //FRESULT_ENTRY(FR_RW_ERROR),
    FRESULT_ENTRY(FR_WRITE_PROTECTED),
    FRESULT_ENTRY(FR_NOT_ENABLED),
    FRESULT_ENTRY(FR_NO_FILESYSTEM),
    FRESULT_ENTRY(FR_INVALID_OBJECT),
    FRESULT_ENTRY(FR_MKFS_ABORTED)
};

const char *g_ppcDirListStrings[NUM_LIST_STRINGS]; // Storage for the filename
                                                   // listbox widget string
                                                   // table.

//
// Storage for the names of the files in the current directory. Filenames
// are stored in format "(D) filename.ext" for directories or
// "(F) filename.ext" for files.
//
char g_pcFilenames[NUM_LIST_STRINGS][MAX_FILENAME_STRING_LEN];

//
// Storage for the strings which appear in the status box at the bottom of the
// display.
//
char g_pcStatus[NUM_STATUS_STRINGS][MAX_STATUS_STRING_LEN];

//
// Storage for the status listbox widget string table.
//
const char *g_ppcStatusStrings[NUM_STATUS_STRINGS] =
{
    g_pcStatus[0],
    g_pcStatus[1],
    g_pcStatus[2],
    g_pcStatus[3],
    g_pcStatus[4],
    g_pcStatus[5]
};
unsigned long g_ulStatusStringIndex = 0;

//
// StringFromFresult - This function returns a string representation of an
//                     error code that was returned from a function call to
//                     FatFs.  It can be used for printing human readable
//                     error messages.
//
static const char *
StringFromFresult(FRESULT fresult)
{
    unsigned int uIdx;

    //
    // Enter a loop to search the error code table for a matching
    // error code.
    //
    for(uIdx = 0; uIdx < NUM_FRESULT_CODES; uIdx++)
    {
        //
        // If a match is found, then return the string name of the
        // error code.
        //
        if(g_sFresultStrings[uIdx].fresult == fresult)
        {
            return(g_sFresultStrings[uIdx].pcResultStr);
        }
    }

    //
    // At this point no matching code was found, so return a
    // string indicating unknown error.
    //
    return("UNKNOWN ERROR CODE");
}

//
// SysTickHandler - This is the handler for this SysTick interrupt.  FatFs
//                  requires a timer tick every 10 ms for internal timing
//                  purposes.
//
__interrupt void
SysTickHandler(void)
{
    //
    // Call the FatFs tick timer.
    //
    disk_timerproc();
    PieCtrlRegs.PIEACK.all |= 1;
}

//
// Cmd_ls - This function implements the "ls" command.  It opens the current
//          directory and enumerates through the contents, and prints a line
//          for each item it finds.  It shows details such as file attributes,
//          time and date, and the file size, along with the name.  It shows a
//          summary of file sizes at the end along with free space.
//
int
Cmd_ls(int argc, char *argv[])
{
    unsigned long ulTotalSize, ulItemCount, ulFileCount, ulDirCount;
    FRESULT fresult;
    FATFS *pFatFs;

    //
    // Open the current directory for access.
    //
    fresult = f_opendir(&g_sDirObject, g_cCwdBuf);

    //
    // Check for error and return if there is a problem.
    //
    if(fresult != FR_OK)
    {
        return(fresult);
    }

    ulTotalSize = 0;
    ulFileCount = 0;
    ulDirCount = 0;
    ulItemCount = 0;

    //
    // Give an extra blank line before the listing.

    //
    // Enter loop to enumerate through all directory entries.
    //
    for(;;)
    {
        //
        // Read an entry from the directory.
        //
        fresult = f_readdir(&g_sDirObject, &g_sFileInfo);

        //
        // Check for error and return if there is a problem.
        //
        if(fresult != FR_OK)
        {
            return(fresult);
        }

        //
        // If the file name is blank, then this is the end of the
        // listing.
        //
        if(!g_sFileInfo.fname[0])
        {
            break;
        }


        //
        // Add the information as a line in the listbox widget.
        //
//        if(ulItemCount < NUM_LIST_STRINGS)
//        {
//            usprintf(g_pcFilenames[ulItemCount], "(%c) %12s",
//                     (g_sFileInfo.fattrib & AM_DIR) ? 'D' : 'F',
//                     g_sFileInfo.fname);
//        }

        //
        // If the attribute is directory, then increment the directory count.
        //
//        if(g_sFileInfo.fattrib & AM_DIR)
//        {
//            ulDirCount++;
//        }
        //
        // Otherwise, it is a file.  Increment the file count, and
        // add in the file size to the total.
        //
        else
        {
            ulFileCount++;
            //ulTotalSize += g_sFileInfo.fsize;
        }

        //
        // Move to the next entry in the item array we use to populate the
        // list box.
        //
        ulItemCount++;

    }

    //
    // Get the free space.
    //
    //fresult = f_getfree("/", &ulTotalSize, &pFatFs);

    //
    // Check for error and return if there is a problem.
    //
    if(fresult != FR_OK)
    {
        return(fresult);
    }



    return ulItemCount;
}

//
// ChangeToDirectory - This function implements the "cd" command.  It takes an
//                     argument that specifies the directory to make the
//                     current working directory. Path separators must use a
//                     forward slash "/".  The argument to cd can be one of the
//                     following:
//                     * root ("/")
//                     * a fully specified path ("/my/path/to/mydir")
//                     * a single directory name that is in the current
//                       directory ("mydir")
//                     * parent directory ("..")
//                     It does not understand relative paths, so don't try
//                     something like this: ("../my/new/path")
//                     Once the new directory is specified, it attempts to open
//                     the directory to make sure it exists.  If the new path
//                     is opened successfully, then the current working
//                     directory (cwd) is changed to the new path. In cases of
//                     error, the pulReason parameter will be written with one
//                     of the following values:
//
static FRESULT
ChangeToDirectory(char *pcDirectory, unsigned long *pulReason)
{
    unsigned int uIdx;
    FRESULT fresult;

    //
    // Copy the current working path into a temporary buffer so
    // it can be manipulated.
    //
    strcpy(g_cTmpBuf, g_cCwdBuf);

    //
    // If the first character is /, then this is a fully specified
    // path, and it should just be used as-is.
    //
    if(pcDirectory[0] == '/')
    {
        //
        // Make sure the new path is not bigger than the cwd buffer.
        //
        if(strlen(pcDirectory) + 1 > sizeof(g_cCwdBuf))
        {
            *pulReason = NAME_TOO_LONG_ERROR;
            return(FR_OK);
        }
        //
        // If the new path name (in argv[1])  is not too long, then
        // copy it into the temporary buffer so it can be checked.
        //
        else
        {
            strncpy(g_cTmpBuf, pcDirectory, sizeof(g_cTmpBuf));
        }
    }
    //
    // If the argument is .. then attempt to remove the lowest level
    // on the CWD.
    //
    else if(!strcmp(pcDirectory, ".."))
    {
        //
        // Get the index to the last character in the current path.
        //
        uIdx = strlen(g_cTmpBuf) - 1;

        //
        // Back up from the end of the path name until a separator (/)
        // is found, or until we bump up to the start of the path.
        //
        while((g_cTmpBuf[uIdx] != '/') && (uIdx > 1))
        {
            //
            // Back up one character.
            //
            uIdx--;
        }

        //
        // Now we are either at the lowest level separator in the
        // current path, or at the beginning of the string (root).
        // So set the new end of string here, effectively removing
        // that last part of the path.
        //
        g_cTmpBuf[uIdx] = 0;
    }
    //
    // Otherwise this is just a normal path name from the current
    // directory, and it needs to be appended to the current path.
    //
    else
    {
        //
        // Test to make sure that when the new additional path is
        // added on to the current path, there is room in the buffer
        // for the full new path.  It needs to include a new separator,
        // and a trailing null character.
        //
        if(strlen(g_cTmpBuf) + strlen(pcDirectory) + 1 + 1 > sizeof(g_cCwdBuf))
        {
            *pulReason = NAME_TOO_LONG_ERROR;
            return(FR_INVALID_OBJECT);
        }
        //
        // The new path is okay, so add the separator and then append
        // the new directory to the path.
        //
        else
        {
            //
            // If not already at the root level, then append a /
            //
            if(strcmp(g_cTmpBuf, "/"))
            {
                strcat(g_cTmpBuf, "/");
            }

            //
            // Append the new directory to the path.
            //
            strcat(g_cTmpBuf, pcDirectory);
        }
    }

    //
    // At this point, a candidate new directory path is in chTmpBuf.
    // Try to open it to make sure it is valid.
    //
    fresult = f_opendir(&g_sDirObject, g_cTmpBuf);

    //
    // If it cant be opened, then it is a bad path.  Inform
    // user and return.
    //
    if(fresult != FR_OK)
    {
        *pulReason = OPENDIR_ERROR;
        return(fresult);
    }
    //
    // Otherwise, it is a valid new path, so copy it into the CWD and update
    // the screen.
    //
    else
    {
        strncpy(g_cCwdBuf, g_cTmpBuf, sizeof(g_cCwdBuf));
    }

    //
    // Return success.
    //
    return(FR_OK);
}

//
// Cmd_cd - This function implements the "cd" command.  It takes an argument
//          that specifies the directory to make the current working directory.
//          Path separators must use a forward slash "/".  The argument to cd
//          can be one of the following:
//          * root ("/")
//          * a fully specified path ("/my/path/to/mydir")
//          * a single directory name that is in the current directory("mydir")
//          * parent directory ("..")
//          It does not understand relative paths, so dont try something like
//          this: ("../my/new/path")
//          Once the new directory is specified, it attempts to open the
//          directory to make sure it exists.  If the new path is opened
//          successfully, then the current working directory (cwd) is changed
//          to the new path.
//
int
Cmd_cd(int argc, char *argv[])
{
    unsigned long ulReason;
    FRESULT fresult;

    //
    // Try to change to the directory provided on the command line.
    //
    fresult = ChangeToDirectory(argv[1], &ulReason);

    //
    // If an error was reported, try to offer some helpful information.
    //
    if(fresult != FR_OK)
    {
        switch(ulReason)
        {
            case OPENDIR_ERROR:

                break;

            case NAME_TOO_LONG_ERROR:

                break;

            default:

                break;
        }
    }

    //
    // Return the appropriate error code.
    //
    return(fresult);
}

//
// Cmd_pwd - This function implements the "pwd" command.  It simply prints the
//           current working directory.
//
int
Cmd_pwd(int argc, char *argv[])
{

    //
    // Return success.
    //
    return(0);
}

//
// Cmd_cat - This function implements the "cat" command.  It reads the contents
//           of a file and prints it to the console.  This should only be used
//           on text files.  If it is used on a binary file, then a bunch of
//           garbage is likely to printed on the console.
//
int
Cmd_cat(int argc, char *argv[])
{
    FRESULT fresult;
    unsigned short usBytesRead;

    //
    // First, check to make sure that the current path (CWD), plus
    // the file name, plus a separator and trailing null, will all
    // fit in the temporary buffer that will be used to hold the
    // file name.  The file name must be fully specified, with path,
    // to FatFs.
    //
    if(strlen(g_cCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_cTmpBuf))
    {

        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_cTmpBuf, g_cCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_cCwdBuf))
    {
        strcat(g_cTmpBuf, "/");
    }

    //
    // Now finally, append the file name to result in a fully specified file.
    //
    strcat(g_cTmpBuf, argv[1]);

    //
    // Open the file for reading.
    //
    fresult = f_open(&g_sFileObject, g_cTmpBuf, FA_READ);

    //
    // If there was some problem opening the file, then return
    // an error.
    //
    if(fresult != FR_OK)
    {
        return(fresult);
    }

    //
    // Enter a loop to repeatedly read data from the file and display it,
    // until the end of the file is reached.
    //
    do
    {
        //
        // Read a block of data from the file.  Read as much as can fit
        // in the temporary buffer, including a space for the trailing null.
        //
        fresult = f_read(&g_sFileObject, g_cTmpBuf, sizeof(g_cTmpBuf) - 1,
                         &usBytesRead);

        //
        // If there was an error reading, then print a newline and
        // return the error to the user.
        //
        if(fresult != FR_OK)
        {

            return(fresult);
        }

        //
        // Null terminate the last block that was read to make it a
        // null terminated string that can be used with printf.
        //
        g_cTmpBuf[usBytesRead] = 0;



        //
        // Continue reading until less than the full number of bytes are
        // read.  That means the end of the buffer was reached.
        //
    }
    while(usBytesRead == sizeof(g_cTmpBuf) - 1);

    //
    // Return success.
    //
    return(0);
}

//*****************************************************************************
//
// This function implements the "write" command.  It writes the contents of the
// second argument into the file specified by the first argument. If the file
// does not exist, it creates a new file with the given file name.
//
//*****************************************************************************
int
Cmd_write(int argc, char *argv[])
{
    FRESULT fresult;
    UINT usBytesWritten;
    unsigned int i = 2;
    char writeBuff[CMD_BUF_SIZE] = {0};

    //
    // First, check to make sure that the current path (CWD), plus the file
    // name, plus a separator and trailing null, will all fit in the temporary
    // buffer that will be used to hold the file name.  The file name must be
    // fully specified, with path, to FatFs.
    //
    if(strlen(g_cCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_cTmpBuf))
    {
        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_cTmpBuf, g_cCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_cCwdBuf))
    {
        strcat(g_cTmpBuf, "/");
    }

    //
    // Append the file name to make a complete file path.
    //
    strcat(g_cTmpBuf, argv[1]);

    //
    // Open the file for writing.
    //
    fresult = f_open(&g_sFileObject, g_cTmpBuf, FA_WRITE | FA_OPEN_EXISTING |FA_OPEN_APPEND);

    //
    // Check for error and return if there is a problem.
    //
    if(fresult != FR_OK)
    {
        return(fresult);
    }

    //
    // Creates the string to be written to a file.
    //
    while(i < argc)
    {
        strcat(writeBuff, argv[i]);

        //
        // Adds a space if necessary.
        //
        if(i < argc-1)
        {
            strcat(writeBuff, " ");
        }
        i++;
    }

    //
    // Writes the string into the given file in arg[1]. if file does not exist,
    // it creates a new file.
    //
    fresult = f_write(&g_sFileObject, writeBuff, strlen(writeBuff), &usBytesWritten);

    //
    // Check for error and return if there is a problem.
    //
    if(fresult != FR_OK)
    {
        return(fresult);
    }

    //
    // Close the file after done with it.
    //
    f_close(&g_sFileObject);

    return(0);
}

//*****************************************************************************
//
// This function implements the "mkdir" command.  It creates a new directory
// with the name given in the argument.
//
//*****************************************************************************
int
Cmd_mkdir(int argc, char *argv[])
{
    FRESULT fresult;
    //
    // First, check to make sure that the current path (CWD), plus the file
    // name, plus a separator and trailing null, will all fit in the temporary
    // buffer that will be used to hold the file name.  The file name must be
    // fully specified, with path, to FatFs.
    //
    if(strlen(g_cCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_cTmpBuf))
    {
        //UARTprintf("Resulting path name is too long\n");
        return(0);
    }

    //
    // Copy the current path to the temporary buffer so it can be manipulated.
    //
    strcpy(g_cTmpBuf, g_cCwdBuf);

    //
    // If not already at the root level, then append a separator.
    //
    if(strcmp("/", g_cCwdBuf))
    {
        strcat(g_cTmpBuf, "/");
    }

    //
    // Append the directory name to make a complete file path to the new
    // directory.
    //
    strcat(g_cTmpBuf, argv[1]);

    //
    // Make a directory with the new file path.
    //
    fresult = f_mkdir(g_cTmpBuf);

    //
    // Check for error and return if there is a problem.
    //
    if(fresult != FR_OK)
    {
        return(fresult);
    }

    return(0);
}

//*****************************************************************************
//
// This function implements the "rm" command.  It removes the file or
// subdirectory specified by the argument.
//
//*****************************************************************************
int
Cmd_rm(int argc, char *argv[])
{
    FRESULT fresult;


    if(strlen(g_cCwdBuf) + strlen(argv[1]) + 1 + 1 > sizeof(g_cTmpBuf))
    {
        return(0);
    }


    strcpy(g_cTmpBuf, g_cCwdBuf);


    if(strcmp("/", g_cCwdBuf))
    {
        strcat(g_cTmpBuf, "/");
    }


    strcat(g_cTmpBuf, argv[1]);


    fresult = f_unlink(g_cTmpBuf);


    if(fresult != FR_OK)
    {
        return(fresult);
    }


    return(0);
}

//
// Cmd_help - This function implements the "help" command.  It prints a simple
//            list of the available commands with a brief description.
//
int
Cmd_help(int argc, char *argv[])
{
    tCmdLineEntry *pEntry;

    pEntry = &g_psCmdTable[0];

    while(pEntry->pcCmd)
    {

        pEntry++;
    }

    return(0);
}

//
// This is the table that holds the command names, implementing functions,
// and brief description.
//
tCmdLineEntry g_psCmdTable[] =
{
    { "help",   Cmd_help,      " : Display list of commands" },
    { "h",      Cmd_help,   "    : alias for help" },
    { "?",      Cmd_help,   "    : alias for help" },
    { "ls",     Cmd_ls,      "   : Display list of files" },
    { "chdir",  Cmd_cd,         ": Change directory" },
    { "cd",     Cmd_cd,      "   : alias for chdir" },
    { "pwd",    Cmd_pwd,      "  : Show current working directory" },
    { "cat",    Cmd_cat,      "  : Show contents of a text file" },
    { "write",  Cmd_write,      ": writes to a file. Creates one if file doesn't exist"},
    { "mkdir",  Cmd_mkdir,      ": makes a new file directory"},
    { "rm",     Cmd_rm,      "   : removes a file or directory"},
    { 0, 0, 0 }
};


void
setupSD(void)
{

    //
    // Set the system tick to fire 100 times per second.
    //
    SysTickInit();
    SysTickPeriodSet(SysCtlClockGet(SYSTEM_CLOCK_SPEED) / 100);
    SysTickIntRegister(SysTickHandler);
    SysTickIntEnable();
    SysTickEnable();

    //
    // Mount the file system, using logical disk 0.
    //
    f_mount(&g_sFatFs, "0:", 1);
    diskResult = disk_initialize(0);

    file_counter = CmdLineProcess("ls");
    char temp[20];
    sprintf(temp, "test%d.txt ", file_counter);
    memcpy(filename, temp, 20);

    //char cmd[40] = "\t \t SD init completed \n";
    //writeSD(cmd);


}
void newSetupSD(void)
{
       //
       // Mount the file system, using logical disk 0.
       //
       f_mount(&g_sFatFs, "0:", 1);
       diskResult = disk_initialize(0);

}
void writeHeader()
{
    char str_init[200];
        sprintf(str_init , "timestamp;AmkStatusFL;AmkStatusFR;AmkStatusRL;AmkStatusRR;TempMotor;ErrorInfo;TempIGBT;TempInverter;TempMotor;");
        writeSD(str_init);
        sprintf(str_init , "ErrorInfo;TempIGBT;TempInverter;TempMotor;ErrorInfo;TempIGBT;TempInverter;TempMotor;ErrorInfo;TempIGBT;TempInverter;");
        writeSD(str_init);
        sprintf(str_init , "ActualVelocityFL;ActualVelocityFR;ActualVelocityRL;ActualVelocityRR;TorqueLimitPositiveFL;TorqueLimitPositiveFR;");
        writeSD(str_init);
        sprintf(str_init , "TorqueLimitPositiveRL;TorqueLimitPositiveRR;TorqueLimitNegativeFL;TorqueLimitNegativeFR;TorqueLimitNegativeRL;");
        writeSD(str_init);
        sprintf(str_init , "TorqueLimitNegativeRR;throttle;steering angle;brake;brake_press;status;actualVelocityKMH;max voltage;min voltage;");
        writeSD(str_init);
        sprintf(str_init , "avg voltage;max temp;min temp;avg temp;bms_lv[0];bms_lv[1];bms_lv[2];bms_lv[3];bms_lv[4];bms_lv[5];bms_lv[6];bms_lv[7];");
        writeSD(str_init);
        sprintf(str_init , "Car voltage;Lem current;current sensor;total power;acceleration x;acceleration y;acceleration z;omega x;omega y;omega z;");
        writeSD(str_init);
        sprintf(str_init , "SuspensionsRL;SuspensionsRR;SuspensionsFR;SuspensionsFL;temp pre rad;temp pre cold;temp post cold;temp pre mot;temp post mot;");
        writeSD(str_init);
        sprintf(str_init , "Gpio bms;Gpio imd;Gpio sdc 1;Gpio sdc 2;Gpio sdc 3;Gpio sdc 4;Gpio sdc 5;Gpio sdc 6;MaxtempNslave\n");
        writeSD(str_init);

}
void createFile()
{
    char temp[20];
    sprintf(temp, "test%d.txt ", file_counter);
    memcpy(filename, temp, 20);
    file_counter++;

}
void createFirstFile()
{
    char temp[20];
    sprintf(temp, "Stest%d.txt ", file_counter);
    memcpy(filename, temp, 20);
    file_counter++;

}

void writeSD(char *str)
{
    char a[290] = "write ";
    strcat(a, filename);
    const char* b = str;
    strcat(a, b);
    CmdLineProcess(a);
}

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}



