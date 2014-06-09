/*!
 * \file            ds_report.h
 * \brief           Interface to generic report data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_REPORT_H
#define PG_GENERAL_LEDGER_DS_REPORT_H

#include <stdio.h>

#include "data_structures.h"

/*!  Opaque data type for report  */
typedef struct ds_report * ds_report;

/*!
 * \brief           Creaes a new report.
 * \returns         The new report, or `NULL` on failure.
 */
ds_report ds_report_create(void);

/*!
 * \brief           Destroys a report and frees resources.
 * \param report    The report to destroy.
 */
void ds_report_destroy(ds_report report);

/*!
 * \brief           Sets the report title.
 * \param report    The report.
 * \param title     The title. This string will be automatically freed when
 * the report is destroyed, so you should not pass a string which you wish
 * to retain.
 */
void ds_report_set_title(ds_report report, ds_str title);

/*!
 * \brief               Sets the report text.
 * \param report        The report.
 * \param report_text   The text. This string will be automatically freed when
 * the report is destroyed, so you should not pass a string which you wish
 * to retain.
 */
void ds_report_set_report_text(ds_report report, ds_str report_text);

/*!
 * \brief           Prints a text report to a file.
 * \param report    The report.
 * \param outfile   A pointer to the file to which to print.
 */
void ds_report_print_text_report(ds_report report, FILE * outfile);

/*!
 * \brief           Adds a header to the report.
 * \param report    The report.
 * \param name      The name of the header.
 * \param value     The value of the header.
 * \returns         `true` on success, `false` otherwise.
 */
bool ds_report_add_header(ds_report report, ds_str name, ds_str value);

#endif      /*  PG_GENERAL_LEDGER_DS_REPORT_H  */

