/*!
 * \file            ds_report.c
 * \brief           Implementation of generic report data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

/*!  UNIX feature test macro  */
#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include <time.h>

#include "data_structures.h"

/*!  Structure to contain a report  */
struct ds_report {
    ds_str title;           /*!<  The report title                  */
    ds_list headers;        /*!<  The report headers                */
    ds_str report_text;     /*!<  The report text                   */
    time_t created_time;    /*!<  The created time of the report    */
};

ds_report ds_report_create(void) {
    ds_report new_report = malloc(sizeof *new_report);
    if ( !new_report ) {
        return NULL;
    }


    new_report->headers = ds_list_create(true, ds_str_destructor);
    if ( !new_report->headers ) {
        free(new_report);
        return NULL;
    }

    new_report->title = NULL;
    new_report->report_text = NULL;
    new_report->created_time = time(NULL);

    return new_report;
}

void ds_report_destroy(ds_report report) {
    ds_list_destroy(report->headers);
    ds_str_destroy(report->title);
    ds_str_destroy(report->report_text);
    free(report);
}

void ds_report_set_title(ds_report report, ds_str title) {
    report->title = title;
}

void ds_report_set_report_text(ds_report report, ds_str report_text) {
    report->report_text = report_text;
}

void ds_report_print_text_report(ds_report report, FILE * outfile) {
    fprintf(outfile, "%s\n", ds_str_cstr(report->title));
    for ( size_t i = 0; i < ds_str_length(report->title); ++i ) {
        printf("=");
    }
    printf("\n");
    fprintf(outfile, "%s", ds_str_cstr(report->report_text));

    struct tm ct;
    struct tm * pct = gmtime_r(&report->created_time, &ct);
    if ( pct ) {
        char buffer[100];
        if ( strftime(buffer, 100, "%A %B %d %Y, %H:%M:%S", pct) ) {
            fprintf(outfile, "Report created on %s UTC.\n", buffer);
        }
    }
}

