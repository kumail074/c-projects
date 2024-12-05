#include <tlpi.h>
#include <err_func.h>
#include <stdarg.h>
#include "enames.c.inc"

#ifdef __GNUC__
__attribute__((__noreturn__))
#endif
static void terminate(Boolean useExit3){
    char *s;

    s = getenv("EF_DUMPCORE");

    if(s != NULL && *s != '\0')
        abort();
    else if(useExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}
static void outputError(Boolean useErr, int err, Boolean flushStdout, const char *format, va_list ap) {
#define BUFSIZE 500
        char buf[BUFSIZE], userMsg[BUFSIZE], errText[BUFSIZE];
        vsnprintf(userMsg, BUFSIZE, format, ap);

        if(useErr)
            snprintf(errText, BUFSIZE, " [%s %s]", (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?", strerror(err));
        else
            snprintf(errText, BUFSIZE, ":");

        snprintf(buf, BUFSIZE, "ERROR%S %S\n", errText, userMsg);

        if(flushStdout)
            fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
}

void errMsg(const char *format, ...){
    va_list arglist;
    int savederrno;
    savederrno = errno;
    va_start(arglist, format);
    outputError(TRUE, errno, TRUE, format, arglist);
    va_end(arglist);
    errno = savederrno;
}

void errExit(const char *format, ...){
    va_list arglist;
    va_start(arglist, format);
    outputError(TRUE, errno, TRUE, format, arglist);
    va_end(arglist);
    terminate(TRUE);
}

void err_exit(const char *format, ...){
    va_list arglist;
    va_start(arglist, format);
    outputError(TRUE, errno, FALSE, format, arglist);
    va_end(arglist);
    terminate(FALSE);
}

void errExitEN(int errnum, const char *format, ...){
    va_list arglist;
    va_start(arglist, format);
    outputError(TRUE, errnum, TRUE, format, arglist);
    va_end(arglist);
    terminate(TRUE);
}

void fatal(const char *format, ...){
    va_list arglist;
    va_start(arglist, format);
    outputError(FALSE, 0, TRUE, format, arglist);
    va_end(arglist);
    terminate(TRUE);
}

void usageErr(const char *format, ...){
    va_list arglist;
    fflush(stdout);

    fprintf(stderr, "Usage: ");
    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);
    fflush(stderr);
    exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...){
    va_list arglist;
    fflush(stdout);
    fprintf(stderr, "command-line usage error: ");
    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);
    fflush(stderr);
    exit(EXIT_FAILURE);
}
