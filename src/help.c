#include <stdio.h>
#include <string.h>

// Store help information for each command
const char *help_all = 
    ".help          Show help information for all commands.\n"
    ".cd            Change the working directory.\n"
    ".changes       Show number of rows affected by the last SQL statement.\n"
    ".clone         Clone data from the current database into NEWDB.\n"
    ".quit          Exit the program.\n"
    ".version       Show source, library, and compiler version information.\n"
    ".databases     List names and files of attached databases.\n"
    ".dump          Render database content as SQL statements.\n"
    ".echo          Turn command echo on or off.\n"
    ".excel         Display output in spreadsheet format.\n"
    ".headers       Turn display of headers on or off.\n"
    ".indexes       Show names of indexes.\n"
    ".mode          Set the output mode.\n"
    ".once          Output for the next SQL command only to a file.\n"
    ".open          Close existing database and reopen the file.\n"
    ".output        Send output to a file or stdout.\n"
    ".prompt        Replace the standard prompts.\n"
    ".quit          Stop interpreting input stream, exit if primary.\n"
    ".read          Read input from a file.\n"
    ".save          Write database to a file.\n"
    ".schema        Show CREATE statements matching the pattern.\n"
    ".separator     Change column and row separators.\n"
    ".show          Show current values for various settings.\n"
    ".tables        List names of tables matching a pattern.\n"
    ".timer         Enable or disable SQL timer.\n"
    ".trace         Output each SQL statement as it is run.\n";

const char *help_backup =
    ".backup ?DB? FILE  Backup the specified DB to FILE.\n"
    "  DB        The target database (default 'main').\n"
    "  FILE      The backup file path.\n";

const char *help_cd =
    ".cd DIRECTORY  Change the working directory to DIRECTORY.\n";

const char *help_changes =
    ".changes on|off  Show the number of rows affected by the last SQL statement.\n";

const char *help_clone =
    ".clone NEWDB  Clone data into NEWDB from the existing database.\n";

const char *help_crnl =
    ".crnl on|off  Translate newline characters to carriage return and newline (CRLF).\n";

const char *help_databases =
    ".databases  List names and files of attached databases.\n";

const char *help_dbconfig =
    ".dbconfig ?op? ?val?  List or change sqlite3_db_config() options.\n";

const char *help_dump =
    ".dump ?OBJECTS?  Render the content of the database as SQL.\n";


const char *help_echo =
    ".echo on|off  Turn command echo on or off.\n";

const char *help_excel =
    ".excel  Display output in a spreadsheet format.\n";


const char *help_headers =
    ".headers on|off  Turn display of headers on or off.\n";

const char *help_help =
    ".help ?-all? ?PATTERN?  Show help text for a specific command or all commands.\n";

const char *help_indexes =
    ".indexes ?TABLE?  Show names of indexes for the specified TABLE.\n";

// const char *help_mode =
//     ".mode MODE ?OPTIONS?  Set the output mode.\n"
//     "  MODE is one of:\n"
//     "    ascii       Columns/rows delimited by 0x1F and 0x1E.\n"
//     "    box         Tables using Unicode box-drawing characters.\n"
//     "    csv         Comma-separated values.\n"
//     "    column      Output in columns (see .width).\n"
//     "    html        HTML <table> code.\n"
//     "    insert      SQL insert statements for TABLE.\n"
//     "    json        Results in a JSON array.\n"
//     "    line        One value per line.\n"
//     "    list        Values delimited by '|'.\n"
//     "    markdown    Markdown table format.\n"
//     "    qbox        Shorthand for 'box --wrap 60 --quote'.\n"
//     "    quote       Escape answers as for SQL.\n"
//     "    table       ASCII-art table.\n"
//     "    tabs        Tab-separated values.\n"
//     "    tcl         TCL list elements.\n"
//     "  Options: (for columnar modes or insert mode)\n"
//     ".    --ww           Shorthand for '--wordwrap 1'.\n"
//     "    --quote        Quote output text as SQL literals.\n"
//     "    --noquote      Do not quote output text.\n"
//     "    TABLE          The name of SQL table used for 'insert' mode.\n";

const char *help_once =
    ".once FILENAME  Output for the next SQL command only to FILE.\n";

const char *help_open =
    ".open ?OPTIONS? ?FILE?  Close existing database and reopen FILE.\n";

const char *help_output =
    ".output ?FILE?          Send output to a file or stdout if FILE is omitted.\n";

const char *help_prompt =
    ".prompt MAIN CONTINUE  Replace the standard prompts.\n";

const char *help_quit =
    ".quit  Stop interpreting input stream and exit if primary.\n";

const char *help_read =
    ".read FILE  Read input from FILE.\n";

const char *help_restore =
    ".restore ?DB? FILE  Restore content of DB from a file.\n";

const char *help_save =
    ".save ?OPTIONS? FILE  Write database to FILE.\n";

const char *help_schema =
    ".schema ?PATTERN?  Show CREATE statements matching the pattern.\n"
    "  Options:\n"
    "    --indent          Try to pretty-print the schema.\n"
    "    --nosys           Omit objects whose names start with 'sqlite_'.\n";

const char *help_separator =
    ".separator COL ?ROW?  Change column and row separators.\n";

const char *help_show =
    ".show  Show current values for various settings.\n";

const char *help_tables =
    ".tables ?TABLE?  List names of tables matching the LIKE pattern TABLE.\n";

const char *help_timer =
    ".timer on|off  Enable or disable SQL timer.\n";

const char *help_trace =
    ".trace ?OPTIONS?  Output each SQL statement as it is run.\n";

const char *help_version =
    ".version  Show source, library, and compiler version information.\n";

// Output detailed help based on command
void print_help(const char *command) {
    if (strcmp(command, ".help all") == 0) {
        printf("%s", help_all);
    } 
    else if (strcmp(command, ".help backup") == 0) {
        printf("%s", help_backup);
    }
    else if (strcmp(command, ".help cd") == 0) {
        printf("%s", help_cd);
    }
    else if (strcmp(command, ".help changes") == 0) {
        printf("%s", help_changes);
    }
    else if (strcmp(command, ".help clone") == 0) {
        printf("%s", help_clone);
    }
    else if (strcmp(command, ".help crnl") == 0) {
        printf("%s", help_crnl);
    }
    else if (strcmp(command, ".help databases") == 0) {
        printf("%s", help_databases);
    }
    else if (strcmp(command, ".help dbconfig") == 0) {
        printf("%s", help_dbconfig);
    }
    else if (strcmp(command, ".help dump") == 0) {
        printf("%s", help_dump);
    }
    else if (strcmp(command, ".help echo") == 0) {
        printf("%s", help_echo);
    }
    else if (strcmp(command, ".help excel") == 0) {
        printf("%s", help_excel);
    }
    else if (strcmp(command, ".help headers") == 0) {
        printf("%s", help_headers);
    }
    else if (strcmp(command, ".help help") == 0) {
        printf("%s", help_help);
    }
    else if (strcmp(command, ".help indexes") == 0) {
        printf("%s", help_indexes);
    }
    else if (strcmp(command, ".help once") == 0) {
        printf("%s", help_once);
    }
    else if (strcmp(command, ".help open") == 0) {
        printf("%s", help_open);
    }
    else if (strcmp(command, ".help output") == 0) {
        printf("%s", help_output);
    }
    else if (strcmp(command, ".help prompt") == 0) {
        printf("%s", help_prompt);
    }
    else if (strcmp(command, ".help quit") == 0) {
        printf("%s", help_quit);
    }
    else if (strcmp(command, ".help read") == 0) {
        printf("%s", help_read);
    }
    else if (strcmp(command, ".help restore") == 0) {
        printf("%s", help_restore);
    }
    else if (strcmp(command, ".help save") == 0) {
        printf("%s", help_save);
    }
    else if (strcmp(command, ".help schema") == 0) {
        printf("%s", help_schema);
    }
    else if (strcmp(command, ".help separator") == 0) {
        printf("%s", help_separator);
    }
    else if (strcmp(command, ".help show") == 0) {
        printf("%s", help_show);
    }
    else if (strcmp(command, ".help tables") == 0) {
        printf("%s", help_tables);
    }
    else if (strcmp(command, ".help timer") == 0) {
        printf("%s", help_timer);
    }
    else if (strcmp(command, ".help trace") == 0) {
        printf("%s", help_trace);
    }
    else if (strcmp(command, ".help version") == 0) {
        printf("%s", help_version);
    }
    else if (strcmp(command, ".help") == 0) {
        printf("%s", help_all);
    }
    else {
        printf("No help found for the command: %s\n", command);
        printf("Type .help all to get help for all commands.\n");
    }
}
