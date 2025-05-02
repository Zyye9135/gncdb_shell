#include <stdio.h>
#include <string.h>

// Store help information for each command
const char *help_all = 
    ".help          Show help information for all commands.\n"
    ".backup        Backup the database to a specified FILE (default 'main').\n"
    ".cd            Change the working directory.\n"
    ".changes       Show number of rows affected by the last SQL statement.\n"
    ".clone         Clone data from the current database into NEWDB.\n"
    ".quit          Exit the program.\n"
    ".version       Show source, library, and compiler version information.\n"
    ".databases     List names and files of attached databases.\n"
    ".dbconfig      List or change sqlite3_db_config() options.\n"
    ".dump          Render database content as SQL statements.\n"
    ".echo          Turn command echo on or off.\n"
    ".excel         Display output in spreadsheet format.\n"
    ".fullschema    Show schema and content of sqlite_stat tables.\n"
    ".headers       Turn display of headers on or off.\n"
    ".import        Import data from a file into a table.\n"
    ".indexes       Show names of indexes.\n"
    ".log           Turn logging on or off.\n"
    ".mode          Set the output mode.\n"
    ".once          Output for the next SQL command only to a file.\n"
    ".open          Close existing database and reopen the file.\n"
    ".output        Send output to a file or stdout.\n"
    ".prompt        Replace the standard prompts.\n"
    ".quit          Stop interpreting input stream, exit if primary.\n"
    ".read          Read input from a file or command output.\n"
    ".restore       Restore content of DB from a file.\n"
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
    "  FILE      The backup file path.\n"
    "  Options:\n"
    "    --append        Use appendvfs.\n"
    "    --async         Write to FILE without journal and fsync().\n";

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
    ".dump ?OBJECTS?  Render the content of the database as SQL.\n"
    "  Options:\n"
    "    --data-only        Output only INSERT statements.\n"
    "    --newlines         Allow unescaped newline characters in the output.\n"
    "    --nosys            Omit system tables (e.g., 'sqlite_stat1').\n"
    "    --preserve-rowids  Include ROWID values in the output.\n";

const char *help_echo =
    ".echo on|off  Turn command echo on or off.\n";

const char *help_excel =
    ".excel  Display output in a spreadsheet format.\n";

const char *help_fullschema =
    ".fullschema ?--indent?  Show schema and content of sqlite_stat tables.\n";

const char *help_headers =
    ".headers on|off  Turn display of headers on or off.\n";

const char *help_help =
    ".help ?-all? ?PATTERN?  Show help text for a specific command or all commands.\n";

const char *help_import =
    ".import FILE TABLE  Import data from FILE into TABLE.\n"
    "  Options:\n"
    "    --ascii              Use \\037 and \\036 as column and row separators.\n"
    "    --csv                Use , and \\n as column and row separators.\n"
    "    --skip N             Skip the first N rows of input.\n"
    "    --schema S           Target table S.TABLE.\n"
    "    -v                   'Verbose' - increase auxiliary output.\n"
    "  Notes:\n"
    "    * If TABLE does not exist, it will be created. The first row of input determines the column names.\n"
    "    * If neither --csv nor --ascii is used, the input mode is derived from the '.mode' output mode.\n"
    "    * If FILE begins with '|', it is a command generating input text.\n";

const char *help_indexes =
    ".indexes ?TABLE?  Show names of indexes for the specified TABLE.\n";

const char *help_log =
    ".log FILE|on|off  Turn logging on or off. FILE can be stderr or stdout.\n";

const char *help_mode =
    ".mode MODE ?OPTIONS?  Set the output mode.\n"
    "  MODE is one of:\n"
    "    ascii       Columns/rows delimited by 0x1F and 0x1E.\n"
    "    box         Tables using Unicode box-drawing characters.\n"
    "    csv         Comma-separated values.\n"
    "    column      Output in columns (see .width).\n"
    "    html        HTML <table> code.\n"
    "    insert      SQL insert statements for TABLE.\n"
    "    json        Results in a JSON array.\n"
    "    line        One value per line.\n"
    "    list        Values delimited by '|'.\n"
    "    markdown    Markdown table format.\n"
    "    qbox        Shorthand for 'box --wrap 60 --quote'.\n"
    "    quote       Escape answers as for SQL.\n"
    "    table       ASCII-art table.\n"
    "    tabs        Tab-separated values.\n"
    "    tcl         TCL list elements.\n"
    "  Options: (for columnar modes or insert mode)\n"
    "    --wrap N       Wrap output lines to no longer than N characters.\n"
    "    --wordwrap B   Wrap or not at word boundaries per B (on/off).\n"
    "    --ww           Shorthand for '--wordwrap 1'.\n"
    "    --quote        Quote output text as SQL literals.\n"
    "    --noquote      Do not quote output text.\n"
    "    TABLE          The name of SQL table used for 'insert' mode.\n";

const char *help_once =
    ".once ?OPTIONS? ?FILE?  Output for the next SQL command only to a file.\n";

const char *help_open =
    ".open ?OPTIONS? ?FILE?  Close existing database and reopen FILE.\n"
    "  Options:\n"
    "    --append        Use appendvfs to append database to the end of FILE.\n"
    "    --deserialize   Load into memory using sqlite3_deserialize().\n"
    "    --hexdb         Load the output of 'dbtotxt' as an in-memory db.\n"
    "    --maxsize N     Set the maximum size for --hexdb or --deserialized database.\n"
    "    --new           Initialize FILE to an empty database.\n"
    "    --nofollow      Do not follow symbolic links.\n"
    "    --readonly      Open FILE in read-only mode.\n"
    "    --zip           FILE is a ZIP archive.\n";

const char *help_output =
    ".output ?FILE?          Send output to a file or stdout if FILE is omitted.\n"
    "  If FILE begins with '|', open it as a pipe.\n"
    "  Options:\n"
    "    --bom            Prefix output with a UTF8 byte-order mark.\n"
    "    -e               Send output to the system text editor.\n"
    "    -x               Send output as CSV to a spreadsheet.\n";

const char *help_prompt =
    ".prompt MAIN CONTINUE  Replace the standard prompts.\n";

const char *help_quit =
    ".quit  Stop interpreting input stream and exit if primary.\n";

const char *help_read =
    ".read FILE  Read input from FILE or command output.\n";

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
    ".trace ?OPTIONS?  Output each SQL statement as it is run.\n"
    "    FILE                Send output to FILE.\n"
    "    stdout              Send output to stdout.\n"
    "    stderr              Send output to stderr.\n"
    "    off                 Disable tracing.\n"
    "    --expanded          Expand query parameters.\n"
    "    --plain             Show SQL as it is input.\n"
    "    --stmt              Trace statement execution (SQLITE_TRACE_STMT).\n"
    "    --profile           Profile statements (SQLITE_TRACE_PROFILE).\n"
    "    --row               Trace each row (SQLITE_TRACE_ROW).\n"
    "    --close             Trace connection close (SQLITE_TRACE_CLOSE).\n";

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
    else if (strcmp(command, ".help fullschema") == 0) {
        printf("%s", help_fullschema);
    }
    else if (strcmp(command, ".help headers") == 0) {
        printf("%s", help_headers);
    }
    else if (strcmp(command, ".help help") == 0) {
        printf("%s", help_help);
    }
    else if (strcmp(command, ".help import") == 0) {
        printf("%s", help_import);
    }
    else if (strcmp(command, ".help indexes") == 0) {
        printf("%s", help_indexes);
    }
    else if (strcmp(command, ".help log") == 0) {
        printf("%s", help_log);
    }
    else if (strcmp(command, ".help mode") == 0) {
        printf("%s", help_mode);
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
